#include <iostream>
#include <fstream>

#include <signal.h>
#include <getopt.h>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/json.h>

#include "controller/core/controller.hpp"

bool should_run = true;
cppcms::service * service;

void sighandler(int sig) {
    std::cout << "Shutting down by interruption from terminal" << std::endl;
    should_run = false;
    service->shutdown();
}

void help(char * progname) {
    std::cout << "USAGE: " << progname << " -c config.json -s schema.sql -l lock.file" << std::endl;
}

int main(int argc, char ** argv) {
    int c;
    char * config_file_path = NULL;
    char * sql_file_path = NULL;
    char * lock_file_path = NULL;

    while ((c = getopt(argc,argv,"c:s:l:?h")) != -1) {
        switch (c) {
            case 'c':
                config_file_path = optarg;
                break;
            case 's':
                sql_file_path = optarg;
                break;
            case 'l':
                lock_file_path = optarg;
                break;
            case 'h':
            case '?':
            default:
                help(argv[0]);
                return 0;
                break;
        }
    }
    if (config_file_path == NULL || sql_file_path == NULL || lock_file_path == NULL) {
        help(argv[0]);
        return 1;
    }

    std::ifstream config_file(config_file_path);
    cppcms::json::value config;
    int lno = -1;
    if (!config.load(config_file,true,&lno)) {
        std::cout << "Error parsing config at line no " << lno << std::endl;
        return 1;
    }
    config.set<std::string>("sql.schema",sql_file_path);
    config.set<std::string>("cms.install_lock_file",lock_file_path);

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
