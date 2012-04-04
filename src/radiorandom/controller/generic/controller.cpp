#include "controller.hpp"

controller::generic::generic(cppcms::service & srv, std::string module_name)
    :
      cppcms::application(srv),
      m_menu_item(module_name)
{
    std::string sql_host;
    std::string sql_dbname;
    std::string sql_user;
    std::string sql_password;

    sql_host     = settings().find("sql.server").get_value<std::string>();
    sql_dbname   = settings().find("sql.database").get_value<std::string>();
    sql_user     = settings().find("sql.user").get_value<std::string>();
    sql_password = settings().find("sql.pass").get_value<std::string>();

    sql.open("postgresql:host=" + sql_host + ";dbname=" + sql_dbname + ";user=" + sql_user + ";password='" + sql_password + "'");

    update_is_installed();
    init_error_codes();

    std::cout << "  [NEW]   " << m_menu_item << std::endl;

    /*
    cppdb::result r = sql << "SELECT * from rights";
    while (r.next()) {
        int id;
        std::string name;
        r >> id >> name;
        std::cout << name << std::endl;
    }
    */
}

controller::generic::~generic() {
    std::cout << "  [DEL]   " << m_menu_item << std::endl;
}


// private


void controller::generic::init_error_codes() {
    m_error_codes[404] = "Not Found";
    m_error_codes[403] = "Access Denied";
}

// protected

void controller::generic::please_install() {
    content::please_install c;
    prepare(c,"index");
    c.menu_item = "installer";
    display(c,"please_install");
}

void controller::generic::error(int code, std::string message) {
    content::error c;
    prepare(c,"error");
    c.code = code;
    if (message.empty()) message = m_error_codes[code];
    if (!message.empty()) {
        c.message = " - " + message;
    }
    display(c,"error");
}

void controller::generic::prepare(content::generic &c, std::string submenu_item) {
    c.is_installed = m_is_installed;
    c.menu_item = m_menu_item;
    c.submenu_item = submenu_item;

    c.menu_items["core"] = "Core";
    c.menu_items["user"] = "User";
    c.menu_items["post"] = "Post";

    cppdb::result r;

    int user_count = 0;

    c.user_name = "baka";
    c.user_password_hash = "zzz";

    sql <<
           "select count(*) from users where name = ? and password_hash = ?"
        << c.user_name
        << c.user_password_hash
        << cppdb::row
        >> user_count;

    if (user_count <= 0) {
        r = sql << "select name from users_static_view where ip = ?" << request().http_host() << cppdb::row;
        if (!r.empty()) {
            r >> c.user_name;
            c.user_logged_in = true;
        } else {
            c.user_name = "anonymous";
            c.user_logged_in = false;
        }
        user_count = 1;
    } else {
        c.user_logged_in = true;
    }

    if (user_count > 0) {
        sql << "select email from users where name = ?" << c.user_name << cppdb::row >> c.user_email;

        r = sql << "select \"group\" from users_groups_view where name = ?" << c.user_name;
        while (r.next()) {
            std::string group;
            r >> group;
            c.user_groups.push_back(group);
        }

        r = sql << "select \"right\" from users_rights_view where name = ?" << c.user_name;
        while (r.next()) {
            std::string right;
            r >> right;
            c.user_rights.push_back(right);
        }
    }
}

void controller::generic::display(content::generic &c, std::string tmpl, std::string skin) {
    render(skin,tmpl,c);
}

void controller::generic::do_dispatch(std::string url) {
    if (!dispatcher().dispatch(url)) {
        if (is_installed()) {
            error(404);
        } else {
            please_install();
        }
    }
}

void controller::generic::update_is_installed() {
    try {
        m_lock_file = settings().find("cms.install_lock_file").get_value<std::string>();
        m_is_installed = util::fs::file_exists(m_lock_file);
    } catch (cppcms::json::bad_value_cast const& e) {
        m_lock_file = "";
        m_is_installed = false;
    }
}

// public

bool controller::generic::is_installed() {
    return m_is_installed;
}

std::string controller::generic::lock_file() {
    return m_lock_file;
}


void controller::generic::main(std::string url) {
    do_dispatch(url);;
}
