#include "controller.hpp"

// static
bool controller::installer::m_static_initialized = false;
wrapper::sql::session controller::installer::m_sql_update;

// public

controller::installer::installer(cppcms::service &srv)
    : generic(srv,"installer")
{
    if (!m_static_initialized) {
        m_static_initialized  = true;
        m_sql_update = a    cquire_static_sql();
    }

    if (!config().get<bool>("cms.is_installed")) {
        attach(new controller::installer_rpc(srv),"rpc","/rpc{1}","/rpc((/.*)?)",1);
        dispatcher().assign("/*",&installer::index,this);
        mapper().assign("");

        dispatcher().assign("/install/*",&installer::install,this);
        mapper().assign("install","/install");

        dispatcher().assign("/install_finished/*(.*)",&installer::install_finished,this,1);
        mapper().assign("install_finished","/install_finished");
    }
}

void controller::installer::index() {
    content::installer::index c;
    prepare(c,"index");
    display(c,"installer_index");
}

void controller::installer::install() {
    content::installer::install c;
    prepare(c,"install");
    display(c,"installer_install");
}


void controller::installer::install_finished(std::string url) {
    mutex().lock("install");
    update_installed_state();
    if (!config().get<bool>("cms.is_installed")) {
        std::cout << "installing" << std::endl;
        std::ifstream schema_template_stream(config().get<std::string>("cms.schema_template").c_str());
        std::vector<std::string> stmts = util::sql::parse_sql_schema(schema_template_stream);
        std::vector<std::string>::const_iterator it;

        controller::installer_rpc::reset();
        controller::installer_rpc::set_state(true);
        controller::installer_rpc::set_total(stmts.size());
        int current = 0;
        sql_update_lock(m_module_name);
        cppdb::transaction guard(m_sql_update);
        for (it = stmts.begin(); it != stmts.end(); ++it) {
            m_sql_update << *it << cppdb::exec;
            ++current;
            controller::installer_rpc::set_current(current);
        }
        guard.commit();
        sql_update_unlock(m_module_name);
        controller::installer_rpc::set_state(false);
        if (url != "silent") {
            content::installer::install_finished c;
            prepare(c,"install_finished");
            display(c,"installer_install_finished");
        }

    }
    service().shutdown();
    util::fs::create_file(config().get<std::string>("cms.install_lock"));
    mutex().unlock("install");
}
