#include <iostream>
#include <fstream>

#include <signal.h>
#include <getopt.h>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/json.h>

#include "controller/core/controller.hpp"

#include <radiorandom/single/single.hpp>

#include <radiorandom/util/util.hpp>

bool should_run = true;
cppcms::service * service;

void sighandler(int sig) {
    std::cout << "Shutting down by interruption from terminal" << std::endl;
    should_run = false;
    service->shutdown();
}

void help(char * progname) {
    std::cout << "USAGE: " << progname << " -w working directory" << std::endl;
}

int main(int argc, char ** argv) {
    int c = -1;
    std::string working_directory;
    std::string config_file_path;
    std::string sql_file_path;
    std::string lock_file_path;
    std::string data_directory;

    while ((c = getopt(argc,argv,"w:h?")) != -1 ) {
        switch (c) {
            case 'w':
                working_directory = optarg;
                break;
            case 'h':
            case '?':
            default:
                std::cout << c;
                help(argv[0]);
                return 0;
                break;
        }
    }
    config_file_path = working_directory + "/config.json";
    sql_file_path    = working_directory + "/schema.sql";
    lock_file_path   = working_directory + "/install.lock";
    data_directory   = working_directory + "/data";

    if (working_directory.empty()) {
        std::cout << "you must specify working directory with `-w working directory' flag." << std::endl;
        return 0;
    }

    if (!util::fs::file_exists(config_file_path)) {
        std::cout << "Configuration file in path `" + config_file_path + "' does not exists!" << std::endl;
        return 1;
    }

    if (!util::fs::file_exists(sql_file_path)) {
        std::cout << "SQL schema file in path `" + sql_file_path + "' does not exists!" << std::endl;
        return 1;
    }

    if (!util::fs::file_exists(data_directory)) {
        std::cout << "Data directory in path `" + data_directory + "' does not exists!" << std::endl;
        return 1;
    }

    std::ifstream config_file(config_file_path.c_str());
    cppcms::json::value config;
    int lno = -1;
    if (!config.load(config_file,true,&lno)) {
        std::cout << "Error parsing config at line no " << lno << std::endl;
        return 1;
    }
    config.set<std::string>("sql.schema",sql_file_path);
    config.set<std::string>("cms.install_lock_file",lock_file_path);
    config.set<std::string>("cms.data_directory",data_directory);

    std::string sql_host;
    std::string sql_dbname;
    std::string sql_user;
    std::string sql_password;

    std::string propname;
    try {
        propname = "sql.server";
        sql_host     = config.find("sql.server").get_value<std::string>();

        propname = "sql.database";
        sql_dbname   = config.find("sql.database").get_value<std::string>();

        propname = "sql.user";
        sql_user     = config.find("sql.user").get_value<std::string>();

        propname = "sql.pass";
        sql_password = config.find("sql.pass").get_value<std::string>();
    } catch (cppcms::json::bad_value_cast const& e) {
        std::cout << "Error reading `" << propname << "' from configuration file: Property does not exists!" << std::endl;
        exit(1);
    }

    single::sql::update.open("postgresql:host=" + sql_host + ";dbname=" + sql_dbname + ";user=" + sql_user + ";password='" + sql_password + "'");

    signal(SIGINT, &sighandler);

    std::cout << "Initialized" << std::endl;
    //std::cout << util::sql::make_password_hash(config.find("security.salt").get_value<std::string>(),"admin") << std::endl;
    //std::cout << util::sql::hash_password(util::sql::salt_password(config.find("security.salt").get_value<std::string>(),"admin")) << std::endl;

    try {
        while (should_run) {
            service = new cppcms::service(config);
            service->applications_pool().mount(cppcms::applications_factory<controller::core>());
            service->run();
            delete service;
        }
    } catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
    }

    single::sql::update.close();
    return 0;
}
