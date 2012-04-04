#ifndef SINGLE_HPP
#define SINGLE_HPP

#include <cppdb/mutex.h>

namespace single {
    namespace sql {
        static cppdb::mutex global_sql_mutex;
    }
}

#endif // SINGLE_HPP
