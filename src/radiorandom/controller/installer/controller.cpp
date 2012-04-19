#include "controller.hpp"

// public

controller::installer::installer(cppcms::service &srv)
    : generic(srv,"installer")
{
    if (controller::installer_rpc::total() > 0) {
        attach(new controller::installer_rpc(srv),"rpc","/rpc{1}","/rpc((/.*)?)",1);
    }

    if (config().get<bool>("cms.is_installed")) {
        return;
    }

    dispatcher().assign("/*",&installer::index,this);
    mapper().assign("");

    dispatcher().assign("/install/*",&installer::install,this);
    mapper().assign("install","/install");

    dispatcher().assign("/install_finished/*(.*)",&installer::install_finished,this,1);
    mapper().assign("install_finished","/install_finished");
}

void controller::installer::index() {
    content::installer::index c;
    display(c,"index","installer_index");
}

void controller::installer::install() {
    content::installer::install c;
    display(c,"install","installer_install");
}

void controller::installer::install_finished(std::string url) {
    mutex().lock("install");
    update_installed_state();
    if (!config().get<bool>("cms.is_installed")) {
        std::cout << "Installing CMS" << std::endl;
        std::ifstream schema_stream(config().get<std::string>("cms.schema_file").c_str());
        std::vector<std::string> stmts = util::sql::parse_sql_schema(schema_stream);
        std::vector<std::string>::const_iterator it;

        controller::installer_rpc::reset();
        controller::installer_rpc::set_state(true);
        controller::installer_rpc::set_total(stmts.size());

        int current = 0;

        sql_guard(m_sql);
        for (it = stmts.begin(); it != stmts.end(); ++it) {
            m_sql << *it << cppdb::exec;
            ++current;
            controller::installer_rpc::set_current(current);
        }
        sql_commit(m_sql);


        controller::installer_rpc::set_state(false);
        std::cout << "Installation finished" << std::endl;
        if (url != "silent") {
            content::installer::install_finished c;
            display(c,"install_finished","installer_install_finished");
        }
    }
    service().shutdown();
    util::fs::create_file(config().get<std::string>("cms.install_lock"));
    mutex().unlock("install");
}
