#include "controller.hpp"

// static

std::map<int,std::string> controller::generic::m_error_codes;
bool controller::generic::m_static_initalized = false;

// public

controller::generic::generic(cppcms::service &srv, std::string const& controller_name, std::string const& service_name)
    : superclass(service_name,controller_name), application(srv)
{
    if (!m_static_initalized) {
        m_static_initalized = true;
        init_error_codes();
        set_config(settings());
    }
    update_installed_state();
    m_sql = acquire_sql(false);
}

controller::generic::~generic() {

}

void controller::generic::main(std::string url) {
    do_dispatch(url);
}

// protected
void controller::generic::prepare(content::generic &c, std::string const& menu_item) {
    c.site_name = config().get<std::string>("branding.site_name");
    c.is_installed = config().get<bool>("cms.is_installed");
    c.module_name = m_controller_name;
    c.menu_item = menu_item;

    c.module_names["core"] = "Core";
    //c.module_names["user"] = "User";

    if (!c.is_installed) {
        c.user.name ="anonymous";
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


void controller::generic::display(content::generic &c, std::string const& menu_item,  std::string const& tmpl, std::string const& skin) {
    prepare(c,menu_item);
    render(skin,tmpl,c);
}

void controller::generic::please_install() {
    content::please_install c;
    prepare(c,"index");
    c.module_name = "installer";
    render("html","please_install",c);
}

void controller::generic::error(int code, std::string message) {
    response().status(code);
    content::error c;
    c.code = code;
    if (message.empty()) message = m_error_codes[code];
    if (!message.empty()) {
        c.message = " - " + message;
    }
    display(c,"error","error");
}

void controller::generic::do_dispatch(const std::string &url) {
    if (!dispatcher().dispatch(url)) {
        if (config().get<bool>("cms.is_installed")) {
            error(404);
        } else {
            please_install();
        }
    }
}

void controller::generic::update_installed_state() {
    config().set<bool>("cms.is_installed",util::fs::file_exists(config().get<std::string>("cms.install_lock")));
}

void controller::generic::sql_guard(wrapper::session &sql) {
    mutex().lock(sql.name());
}

void controller::generic::sql_commit(wrapper::session &sql) {
    mutex().unlock(sql.name());
}

wrapper::session & controller::generic::acquire_sql(bool is_static) {
    return sql().acquire(m_controller_name,is_static);
}

// private
void controller::generic::init_error_codes() {
    m_error_codes[403] = "Access Denied";
    m_error_codes[404] = "Not Found";
}
