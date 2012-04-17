#include "controller.hpp"

controller::installer::installer(cppcms::service &srv)
    : generic(srv,"installer")
{
    attach(new controller::installer_rpc(srv),"rpc","/rpc{1}","/rpc((/.*)?)",1);
    if (!config().get<bool>("cms.is_installed")) {
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
        std::vector<std::string>::const_iterator it,end;

        controller::installer_rpc::reset();
        controller::installer_rpc::set_state(true);
        controller::installer_rpc::set_total(stmts.size());
        int current = 0;
        mutex().lock("sql");
        for (it = stmts.begin(); it != stmts.end(); ++it) {
            m_sql << *it << cppdb::exec;
            ++current;
            controller::installer_rpc::set_current(current);
        }
        mutex().unlock("sql");
        controller::installer_rpc::set_state(false);
        if (url != "silent") {
            content::installer::install_finished c;
            prepare(c,"install_finished");
            display(c,"installer_install_finished");
        }

    }
    std::cout << config().get<std::string>("cms.instal_lock") << std::endl;
    util::fs::create_file(config().get<std::string>("cms.install_lock"));
    service().shutdown();
    mutex().unlock("install");
}
