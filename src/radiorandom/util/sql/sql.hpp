#ifndef SQL_HPP
#define SQL_HPP

#include <vector>
#include <string>
#include <fstream>

namespace util {
    namespace sql {
        std::vector<std::string> read_file_to_stmts(std::string const& filename);
    }
}

#endif // SQL_HPP
