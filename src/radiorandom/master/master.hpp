#ifndef MASTER_HPP
#define MASTER_HPP

#include <string>

#include <cppcms/service.h>

#include <cppdb/frontend.h>
#include <cppdb/mutex.h>

namespace master {
    namespace cms {
        static bool should_run = true;
        static cppcms::service * service = NULL;
        static std::string working_directory;
        static std::string lock_file;
        static std::string config_file;
        static std::string data_directory;
        static std::string schema_template;
    }
    namespace sql {
        static cppdb::mutex mutex;
        static cppdb::session update;
        static std::string host;
        static std::string dbname;
        static std::string user;
        static std::string password;
        static std::string sql_connect_string;
    }
}

#endif
