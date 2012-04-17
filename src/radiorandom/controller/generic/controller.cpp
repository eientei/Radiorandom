#include "controller.hpp"

// static
std::map<int,std::string> controller::generic::m_error_codes;

// public
controller::generic::generic(cppcms::service &srv, std::string const& module_name)
    : application(srv), m_module_name(module_name)
{
    update_installed_state();
    m_sql = sql().session(m_module_name);
    m_sql.open(config().get<std::string>("sql.connection_string"));
    std::cout << "      [NEW]   " << m_module_name << std::endl;
}

controller::generic::~generic() {
    sql().close(m_module_name);
    std::cout << "      [DEL]   " << m_module_name << std::endl;
}

void controller::generic::main(std::string url) {
    do_dispatch(url);
}

// protected
void controller::generic::prepare(content::generic &c, std::string const& submodule_name) {
    c.site_name = config().get<std::string>("branding.site_name");
    c.is_installed = config().get<bool>("cms.is_installed");
    c.menu_item = m_module_name;
    c.submenu_item = submodule_name;

    c.menu_items["core"] = "Core";
    //c.menu_items["user"] = "User";
    //c.menu_items["post"] = "Post";


    if (!c.is_installed) {
        c.user.name = "anonymous";
        c.user.logged_in = false;
        c.user.rights.push_back("view");
        return;
    }

    int user_count;
    cppdb::result r;

    c.user.name = "baka";
    c.user.password_hash = "zzz";

    m_sql << "select count(*) from users where name = ? and password_hash = ?"
        << c.user.name
        << c.user.password_hash
        << cppdb::row
        >> user_count;

    if (user_count == 0) {
        r = m_sql << "select name from users_static_view where ip = ?"
                << request().http_host()
                << cppdb::row;
        if (!r.empty()) {
            r >> c.user.name;
            c.user.logged_in = true;
        } else {
            c.user.name = "anonymous";
            c.user.logged_in = false;
        }
        user_count = 1;
    }

    if (user_count > 0) {
        m_sql << "select email from users where name = ?"
            << c.user.name
            << cppdb::row
            >> c.user.email;

        r = m_sql << "select \"group\" from users_groups_view where name = ?"
                << c.user.name;
        while (r.next()) {
            std::string group;
            r >> group;
            c.user.groups.push_back(group);
        }

        r = m_sql << "select \"right\" from users_rights_view where name = ?"
                << c.user.name;
        while (r.next()) {
            std::string right;
            r >> right;
            c.user.rights.push_back(right);
        }
    }

}


void controller::generic::please_install() {
    content::please_install c;
    prepare(c,"index");
    c.menu_item = "installer";
    display(c,"please_install");
}

void controller::generic::error(int code, std::string message) {
    response().status(code);
    content::error c;
    prepare(c,"error");
    c.code = code;
    if (message.empty()) message = m_error_codes[code];
    if (!message.empty()) {
        c.message = " - " + message;
    }
    display(c,"error");
}

void controller::generic::display(content::generic & c, std::string const& tmpl, std::string const& skin) {
    render(skin,tmpl,c);
}

void controller::generic::do_dispatch(std::string const& url) {
    if (!dispatcher().dispatch(url)) {
        if (config().get<bool>("cms.is_installed")) {
            error(404);
        } else {
            please_install();
        }
    }
}

void controller::generic::update_installed_state() {
    config().set("cms.is_installed") = util::fs::file_exists(config().get<std::string>("cms.install_lock"));
}

// private
void controller::generic::init_error_codes() {
    m_error_codes[403] = "Access Denied";
    m_error_codes[404] = "Not Found";
}
