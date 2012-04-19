#ifndef CORE_EXECUTOR_HPP
#define CORE_EXECUTOR_HPP

#include <string>
#include <vector>

#include <stdlib.h>
#include <signal.h>

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/json.h>
#include <cppcms/applications_pool.h>

#include <radiorandom/controller/core/controller.hpp>

#include <radiorandom/util/string/util.hpp>
#include <radiorandom/util/fs/util.hpp>

namespace core {
    class executor {
        public:
            executor(int argc, char ** argv);
            ~executor();
        public:
            void run();
            void shutdown();
        public:
            static void sighandler(int sigc);
            static cppcms::json::value & config();
        private:
            void parse_args(int argc, char ** argv);
            void validate_args();
            void load_config();
            void populate_config();
        private:
            void print_help(std::string const& prog);
            void assure_exists(std::string const& path, std::string const& name);
        private:
            static executor * m_instance;
            static bool m_should_run;
            static cppcms::service * m_service;
            static cppcms::json::value m_config;
        private:
            std::string m_working_directory;
    };
}

#endif // CORE_EXECUTOR_HPP
