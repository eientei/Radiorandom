#include "core.hpp"

// static

cppcms::json::value core::executor::m_config;
core::executor * core::executor::m_instance = NULL;
cppcms::service * core::executor::m_service = NULL;
bool core::executor::m_should_run = false;

// public

core::executor::executor(int argc, char ** argv) {
    std::cout << "Initializing..." << std::endl;

    if (m_instance != NULL) {
        throw std::runtime_error("Already running!");
    }

    m_should_run = true;
    m_instance = this;
    parse_args(argc,argv);
    load_config();
    signal(SIGINT,&sighandler);


    std::cout << "Initialized" << std::endl;
}

core::executor::~executor() {
    m_instance = NULL;
    std::cout << "Deinitialized" << std::endl;
}

void core::executor::run() {
    while (m_should_run) {
        std::cout << "Fired up" << std::endl;
        m_service = new cppcms::service(m_config);
        m_service->applications_pool().mount(cppcms::applications_factory<controller::core>());
        m_service->run();
        delete m_service;
        m_service = NULL;
        std::cout << "Shutted down" << std::endl;
    }
}



void core::executor::shutdown() {
    std::cout << std::endl;
    if (!m_should_run) {
        std::cout << "Forced interruption!" << std::endl;
        exit(1);
    }
    m_should_run = false;
    if (m_service != NULL) {
        m_service->shutdown();
    }
}

void core::executor::sighandler(int sigc) {
    m_instance->shutdown();
}

cppcms::json::value & core::executor::config() {
    return m_config;
}

// private

void core::executor::parse_args(int argc, char **argv) {
    m_working_directory = ".";
    int c;
    while ((c = getopt(argc,argv,"w:?h")) != -1) {
        switch(c) {
            case 'w':
                m_working_directory = optarg;
                break;
            case '?':
            case 'h':
            default:
                print_help(argv[0]);
                exit(0);
                break;
        }
    }
}

void core::executor::load_config() {
    std::string install_lock   = m_working_directory + "/install.lock";
    std::string config_file    = m_working_directory + "/config.json";
    std::string schema_file    = m_working_directory + "/schema.sql";
    std::string data_directory = m_working_directory + "/data";
    std::string js_directory   = m_working_directory + "/js";

    assure_exists(m_working_directory,"Working path directory");
    assure_exists(config_file,"Config file");
    assure_exists(schema_file,"Schema template file");
    assure_exists(data_directory,"Data directory");
    assure_exists(js_directory,"Javascript directory");

    std::ifstream config_file_stream(config_file.c_str());
    int no = 0;
    if (!m_config.load(config_file_stream,true,&no)) {
        throw std::runtime_error("Error in config file `" + config_file + "' at line " + util::string::to_string(no));
    }
    config_file_stream.close();

    m_config.set<std::string>("cms.working_directory",m_working_directory);
    m_config.set<std::string>("cms.install_lock",install_lock);
    m_config.set<std::string>("cms.schema_file",schema_file);
    m_config.set<std::string>("cms.data_directory",data_directory);
        m_config.set<std::string>("cms.js_directory",js_directory);
}

// private

void core::executor::print_help(std::string const& prog) {
    std::cout << "USAGE: " << prog << " -w working_directory" << std::endl;
    exit(0);
}

void core::executor::assure_exists(std::string const& path, std::string const& name) {
    if (!util::fs::file_exists(path)) {
        throw std::runtime_error("Not found: `" + path + "' - " + name);
    }

}
