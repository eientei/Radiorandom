#include <iostream>
#include <fstream>

#include <signal.h>
#include <getopt.h>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/json.h>

#include "controller/core/controller.hpp"

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


    signal(SIGINT, &sighandler);

    std::cout << "Initialized" << std::endl;


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
    return 0;
}
