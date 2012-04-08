#include "controller.hpp"

// static

std::map<std::string,booster::shared_ptr<cppdb::mutex> > controller::generic::m_mutexes;
cppdb::session controller::generic::m_update_sql;
bool controller::generic::m_static_initialized = false;
bool controller::generic::m_is_installed = false;
std::string controller::generic::m_schema_template;
std::string controller::generic::m_connection_string;
std::string controller::generic::m_lock_file;
std::map<int,std::string> controller::generic::m_error_codes;

// public

controller::generic::generic(cppcms::service &srv, std::string const& module_name)
    : application(srv), m_menu_item(module_name)
{
    if (!m_static_initialized) {
        init_static_context();
    }

    sql.open(m_connection_string);
    std::cout << "  [NEW]   " << m_menu_item << std::endl;
}

controller::generic::~generic() {
    std::cout << "  [DEL]   " << m_menu_item << std::endl;
}

bool controller::generic::is_installed() {
    return m_is_installed;
}

std::string const& controller::generic::lock_file() {
    return m_lock_file;
}

std::string const& controller::generic::schema_template() {
    return m_schema_template;
}

void controller::generic::main(std::string url) {
    do_dispatch(url);
}



void controller::generic::lock(std::string const& name) {
    mutex_const_iterator it = m_mutexes.find(name);
    if (it == m_mutexes.end()) {
        m_mutexes[name] = booster::shared_ptr<cppdb::mutex>(new cppdb::mutex);
    }
    m_mutexes[name]->lock();

}

void controller::generic::unlock(std::string const& name) {
    mutex_const_iterator it = m_mutexes.find(name);
    if (it != m_mutexes.end()) {
        m_mutexes[name]->unlock();
    }

}

void controller::generic::unlock_all() {
    for (mutex_iterator it = m_mutexes.begin(); it != m_mutexes.end(); ++it) {
        it->second->unlock();
    }
    m_mutexes.clear();
}

void controller::generic::update(std::string const& stmt) {
    lock("global_sql_mutex");
    m_update_sql << stmt << cppdb::exec;
    unlock("global_sql_mutex");
}

void controller::generic::update(std::istream & stream) {
    lock("global_sql_mutex");

    std::string stmt;

    int c = -1;
    bool instring = false;

    while ((c=stream.get()) != -1) {
        char ch = (char)c;
        stmt.push_back(ch);
        switch (ch) {
            case '\'':
                if (!instring) {
                    instring = true;
                } else {
                    if ('\'' == (char)stream.peek()) {
                        stream.get();
                    } else {
                        instring = false;
                    }
                }
                break;
            case ';':
                if (!instring) {
                    m_update_sql << stmt << cppdb::exec;
                    stmt.clear();
                }
                break;
        }
    }

    unlock("global_sql_mutex");
}



// protected

void controller::generic::prepare(content::generic &c, std::string const& submodule_name) {
    c.is_installed = m_is_installed;
    c.menu_item = m_menu_item;
    c.submenu_item = submodule_name;

    c.menu_items["core"] = "Core";
    c.menu_items["user"] = "User";
    c.menu_items["post"] = "Post";

    cppdb::result r;

    int user_count = 0;

    // some cookie magic will be here
    c.user.name = "baka";
    c.user.password_hash = "zzz";

    sql << "select count(*) from users where name = ? and password_hash = ?"
        << c.user.name
        << c.user.password_hash
        << cppdb::row
        >> user_count;

    if (user_count == 0) {
        r = sql << "select name from users_static_view where ip = ?"
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
        sql << "select email from users where name = ?"
            << c.user.name
            << cppdb::row
            >> c.user.email;

        r = sql << "select \"group\" from users_groups_view where name = ?"
                << c.user.name;
        while (r.next()) {
            std::string group;
            r >> group;
            c.user.groups.push_back(group);
        }

        r = sql << "select \"right\" from users_rights_view where name = ?"
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

void controller::generic::do_dispatch(std::string const& url){
    if (!dispatcher().dispatch(url)) {
        if (is_installed()) {
            error(404);
        } else {
            please_install();
        }
    }
}

void controller::generic::update_installed_state() {
    m_is_installed = util::fs::file_exists(m_lock_file);
}

// private

void controller::generic::init_error_codes() {
    m_error_codes[404] = "Not Found";
    m_error_codes[403] = "Access Denied";
}

void controller::generic::init_static_context() {
    m_connection_string = settings().find("sql.connection_string").get_value<std::string>();
    m_lock_file = settings().find("cms.lock_file").get_value<std::string>();
    m_schema_template = settings().find("cms.schema_template").get_value<std::string>();
    m_update_sql.open(m_connection_string);
    m_static_initialized = true;
    update_installed_state();
    init_error_codes();
}
