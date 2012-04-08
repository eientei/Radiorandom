#ifndef EXECUTOR_CORE_HPP
#define EXECUTOR_CORE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <stdexcept>

#include <stdlib.h>
#include <signal.h>

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/json.h>
#include <cppcms/applications_pool.h>


#include <radiorandom/controller/core/controller.hpp>

#include <radiorandom/util/string/util.hpp>
#include <radiorandom/util/fs/util.hpp>

namespace executor {
    class already_running : public std::runtime_error {
        public:
            already_running();
            already_running(std::string const& message);
    };

    class configuration_parse_error : public std::runtime_error {
        public:
            configuration_parse_error();
            configuration_parse_error(std::string const& message);
            configuration_parse_error(std::string const& file, int line_no);
    };

    class file_not_found : public std::runtime_error {
        public:
            file_not_found();
            file_not_found(std::string const& file);
    };


    class core {
        public:
            core(int argc, char ** argv);
            ~core();

            void run();
            void shutdown();
            cppcms::json::value config();
            static void sighandler(int sigc);

        private:
            void parse_args();
            void validate_args();
            void load_config();
            void populate_config();
            void print_help();
            void assure_exists(std::string const& path, std::string const& name);
        private:
            static core * m_instance;
            static bool m_should_run;
            static cppcms::service * m_service;

            int     m_argc;
            char ** m_argv;
            std::vector<std::string> m_args;

            cppcms::json::value m_config;

            std::string m_working_directory;
            std::string m_config_file;
            std::string m_lock_file;
            std::string m_data_directory;
            std::string m_schema_template;
    };
}

#endif // EXECUTOR_CORE_HPP
