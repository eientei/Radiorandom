#include "controller.hpp"

// static

bool controller::user::m_static_initialized = false;
cppdb::session controller::user::m_sql_update;

// public

controller::user::user(cppcms::service &srv)
    : generic(srv,"user")
{
    if (!m_static_initialized) {
        m_static_initialized  = true;
        m_sql_update = acquire_static_sql();
    }
    dispatcher().assign("/*",&user::index,this);
    mapper().assign("");

    dispatcher().assign("/baka/*",&user::foo,this);
}

void controller::user::index() {
    content::user::index c;
    prepare(c,"index");
    display(c,"user_index");
}

void controller::user::foo() {
    content::user::index c;
    data::user baka;
    add_user(baka);
    prepare(c,"index");
    display(c,"user_index");
}

void controller::user::add_user(const data::user &user_data) {
    sql_update_lock("user");
    cppdb::transaction guard(m_sql_update);
    std::ifstream schema_template_stream(config().get<std::string>("cms.schema_template").c_str());
    std::vector<std::string> stmts = util::sql::parse_sql_schema(schema_template_stream);
    for (std::vector<std::string>::const_iterator it = stmts.begin(); it != stmts.end(); ++it) {
        m_sql_update << *it << cppdb::exec;
    }
    guard.commit();
    sql_update_unlock("user");
}
