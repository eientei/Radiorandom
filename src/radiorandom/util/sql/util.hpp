#ifndef UTIL_SQL_HPP
#define UTIL_SQL_HPP

#include <string>
#include <vector>
#include <fstream>

namespace util {
    namespace sql {
        std::vector<std::string> parse_sql_schema(std::istream & stream);
    }
}

#endif // UTIL_SQL_HPP
