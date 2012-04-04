#ifndef SINGLE_HPP
#define SINGLE_HPP

#include <iostream>
#include <fstream>

#include <cppdb/frontend.h>
#include <cppdb/mutex.h>

namespace single {
    namespace sql {
        static cppdb::mutex global_sql_mutex;
        static cppdb::session update;
        void perform_update(std::string const& stmt);
        void perform_update(std::istream & stream);
    }
}

#endif // SINGLE_HPP
