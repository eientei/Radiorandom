#include "controller.hpp"

controller::installer::installer(cppcms::service &srv) : generic(srv,"installer") {
    dispatcher().assign("/*",&controller::installer::index,this);
    mapper().assign("");

    dispatcher().assign("/install/*",&controller::installer::install,this);
    mapper().assign("install","/install");

    dispatcher().assign("/install_finished/*",&controller::installer::install_finished,this);
    mapper().assign("install_finished","/install_finished");
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

void controller::installer::install_finished() {

    //single::sql::global_sql_mutex.lock();
    update_is_installed();
    if (!is_installed()) {
        std::string schema_file_path = settings().find("sql.schema").get_value<std::string>();
        std::ifstream schema_file(schema_file_path.c_str());

        single::sql::perform_update(schema_file);
        /*
        std::vector<std::string> sql_stmts = util::sql::read_file_to_stmts(schema_file_path);


        for (std::vector<std::string>::const_iterator it = sql_stmts.begin(); it != sql_stmts.end(); it++) {
            sql << *it << cppdb::exec;
        }
        */

        util::fs::create_file(lock_file());

        content::installer::install_finished c;
        prepare(c,"install_finished");
        display(c,"installer_install_finished");
    }
    //single::sql::global_sql_mutex.unlock();

    service().shutdown();
}
