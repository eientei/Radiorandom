#include "controller.hpp"

// static

controller::installer_rpc * controller::installer::installer::m_rpc = NULL;

// public

controller::installer::installer(cppcms::service &srv)
    : generic(srv,"installer")
{
    m_rpc = new installer_rpc(srv);

    add(*m_rpc,"rpc","/rpc{1}","/rpc((/.*)?)",1);

    dispatcher().assign("/*",&controller::installer::index,this);
    mapper().assign("");

    dispatcher().assign("/install/*",&controller::installer::install,this);
    mapper().assign("install","/install");

    dispatcher().assign("/install_finished/*(.*)",&controller::installer::install_finished,this,1);
    mapper().assign("install_finished","/install_finished");
}

controller::installer::~installer() {
    delete m_rpc;
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
    lock("install_finished");
    update_installed_state();
    if (!is_installed()) {
        std::cout << "installing" << std::endl;
        std::ifstream schema_template_stream(schema_template().c_str());
        std::vector<std::string> stmts = util::sql::parse_sql_schema(schema_template_stream);
        int total = stmts.size();
        int current = 0;
        m_rpc->set_total_objects(total);
        //m_rpc->reset();
        m_rpc->set_install_state(true);
        lock("global_sql_mutex");

        for (std::vector<std::string>::const_iterator it = stmts.begin(); it != stmts.end(); it++) {
            update() << *it << cppdb::exec;
            current++;
            m_rpc->set_current_objects(current);
        }
        unlock("global_sql_mutex");
        m_rpc->set_install_state(false);
        if (url != "silent") {
            content::installer::install_finished c;
            prepare(c,"install_finished");
            display(c,"installer_install_finished");
        }
    }
    unlock("install_finished");
}
