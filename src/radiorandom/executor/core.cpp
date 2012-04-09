#include "core.hpp"


// static

executor::core * executor::core::m_instance = NULL;
bool executor::core::m_should_run = true;
cppcms::service * executor::core::m_service = NULL;

// public

executor::core::core(int argc, char **argv) {
    std::cout << "Initializing..." << std::endl;
    if (m_instance != NULL) {
        throw already_running();
    }
    m_instance = this;
    m_argc = argc;
    m_argv = argv;
    for (int i = 0; i < argc; ++i) {
        m_args.push_back(m_argv[i]);
    }
    parse_args();
    validate_args();
    load_config();
    populate_config();
    m_service = new cppcms::service(m_config);
    m_service->applications_pool().mount(cppcms::applications_factory<controller::core>());
    signal(SIGINT,&sighandler);
    std::cout << "Initialized" << std::endl;
}

executor::core::~core() {
    m_instance = NULL;
    delete m_service;
    m_service = NULL;
    std::cout << "Deinitialized" << std::endl;
}

void executor::core::run() {
    while (m_should_run) {
        std::cout << "Fired up" << std::endl;
        m_service->run();
        std::cout << "Shutted down" << std::endl;
    }
}

cppcms::json::value executor::core::config() {
    return m_config;
}

void executor::core::shutdown() {
    if (!m_should_run) {
        std::cout << "Forced interruption!" << std::endl;
        exit(1);
    }
    m_should_run = false;
    if (m_service != NULL) {
        m_service->shutdown();
    }
}

void executor::core::sighandler(int sigc) {
    m_instance->shutdown();
}

// private

void executor::core::parse_args() {
    int c = -1;
    while ((c = getopt(m_argc,m_argv,"w:?h")) != -1) {
        switch (c) {
            case 'w':
                m_working_directory = optarg;
                break;
            case '?':
            case 'h':
            default:
                print_help();
                exit(1);
                break;
        }
    }
    if (m_working_directory.empty()) {
        m_working_directory = ".";
    }
    m_config_file     = m_working_directory + "/config.json";
    m_lock_file       = m_working_directory + "/install.lock";
    m_data_directory  = m_working_directory + "/data";
    m_js_directory    = m_working_directory + "/js";
    m_schema_template = m_working_directory + "/schema.sql";
}

void executor::core::validate_args() {
    assure_exists(m_working_directory,"Working path directory");
    assure_exists(m_config_file,"Config file");
    assure_exists(m_schema_template,"Schema template file");
    assure_exists(m_data_directory,"Data directory");
    assure_exists(m_js_directory,"Javascript directory");
}

void executor::core::load_config() {
    std::ifstream config_file(m_config_file.c_str());
    int no = 0;
    if (!m_config.load(config_file,true,&no)) {
        throw configuration_parse_error(m_config_file,no);
    }
    config_file.close();
}

void executor::core::populate_config() {
    std::string host;
    std::string dbname;
    std::string user;
    std::string password;

    std::string propname;

    try {
        propname = "sql.host";
        host = m_config.find(propname).get_value<std::string>();

        propname = "sql.dbname";
        dbname = m_config.find(propname).get_value<std::string>();

        propname = "sql.user";
        user = m_config.find(propname).get_value<std::string>();

        propname = "sql.password";
        password = m_config.find(propname).get_value<std::string>();
    } catch (cppcms::json::bad_value_cast const& e) {
        throw configuration_parse_error("Missing property `" + propname + "' in configuration file");
    }

    std::string connection_string
            = "postgresql:host="
            + host
            + ";dbname="
            + dbname
            + ";user="
            + user
            + ";password='"
            + password
            + "'";

    controller::generic::config().set("cms.working_directory") = m_working_directory;
    controller::generic::config().set("cms.install_lock")      = m_lock_file;
    controller::generic::config().set("cms.config_file")       = m_config_file;
    controller::generic::config().set("cms.schema_template")   = m_schema_template;
    controller::generic::config().set("cms.data_directory")    = m_data_directory;
    controller::generic::config().set("cms.js_directory")      = m_js_directory;
    controller::generic::config().set("sql.connection_string") = connection_string;
}

void executor::core::print_help() {
    std::cout << "USAGE: " << m_argv[0] << " -w working_directory" << std::endl;
    exit(0);
}

void executor::core::assure_exists(std::string const& path, std::string const& name) {
    if (!util::fs::file_exists(path)) {
        throw file_not_found("`" + path + "' - " + name);
    }

}

