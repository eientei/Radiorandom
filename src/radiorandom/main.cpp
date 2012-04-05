#include <iostream>
#include <fstream>

#include <signal.h>
#include <getopt.h>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/json.h>

#include <radiorandom/master/master.hpp>

#include <radiorandom/util/fs/fs.hpp>

void sighandler(int sig) {
    std::cout << "Shutting down by interaption from terminal" << std::endl;
    master::cms::should_run = false;
    if (master::cms::service != NULL) {
        master::cms::service->shutdown();
    }
}

void help(std::string const& progname) {
    std::cout << "USAGE: " << progname << " -w working_directory" << std::endl;
}

void test_exists(std::string const& file, std::string const& name) {
    if (!util::fs::file_exists(file)) {
        std::cout << name << " `" + file + "' does not exists!" << std::endl;
        exit(1);
    }
}

int main(int argc, char ** argv) {
    int c;
    while ((c = getopt(argc,argv,"w:h?")) != -1) {
        switch(c) {
            case 'w':
                master::cms::working_directory = optarg;
                break;
            case 'h':
            case '?':
            default:
                help(argv[0]);
                return 0;
                break;
        }
    }
    if (master::cms::working_directory.empty()) {
        master::cms::working_directory = ".";
    }
    if (!util::fs::file_exists(master::cms::working_directory)) {
        std::cout << "Working directory `" + master::cms::working_directory + "' does not exists!" << std::endl;
        return 1;
    }
    master::cms::config_file     = master::cms::working_directory + "/config.json";
    master::cms::lock_file       = master::cms::working_directory + "/install.lock";
    master::cms::data_directory  = master::cms::working_directory + "/data";
    master::cms::schema_template = master::cms::working_directory + "/schema.sql";

    test_exists(master::cms::config_file,"Config file");
    test_exists(master::cms::data_directory,"Data directory");
    test_exists(master::cms::schema_template,"Schema template");

    std::ifstream config_file(master::cms::config_file.c_str());
    cppcms::json::value config;

    int no = -1;
    if (!config.load(config_file,true,&no)) {
        std::cout << "Error parsing config file `" << master::cms::config_file << "' at line no " << no << std::endl;
        exit(1);
    }

    config.set<std::string>("cms.config_file",master::cms::config_file);
    config.set<std::string>("cms.lock_file",master::cms::lock_file);
    config.set<std::string>("cms.data_directory",master::cms::data_directory);
    config.set<std::string>("cms.schema_template",master::cms::schema_template);

    std::string propname;
    try {
        propname = "sql.server";
        master::sql::host = config.find(propname).get_value<std::string>();
        propname = "sql.database";
        master::sql::dbname = config.find(propname).get_value<std::string>();
        propname = "sql.user";
        master::sql::user = config.find(propname).get_value<std::string>();
        propname = "sql.pass";
        master::sql::password = config.find(propname).get_value<std::string>();
    } catch (cppcms::json::bad_value_cast const& e) {
        std::cout << "Error reading `" << propname << "' from configuration file: Property does not exists!" << std::endl;
        exit(1);
    }

    master::sql::sql_connect_string =
            "postgresql:host="
            + master::sql::host
            + ";dbname="
            + master::sql::dbname
            + ";user="
            + master::sql::user
            + ";password='"
            + master::sql::password
            + "'";

    master::sql::update.open(master::sql::sql_connect_string);

    signal(SIGINT,&sighandler);

    std::cout << "Initialized" << std::endl;



    master::sql::update.close();
    std::cout << "Deinitialized" << std::endl;
    return 0;
}
