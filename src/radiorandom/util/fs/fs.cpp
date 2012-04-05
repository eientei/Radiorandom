#include "fs.hpp"

bool util::fs::file_exists(const std::string &filename) {
    return std::ifstream(filename.c_str()) != NULL;
}

void util::fs::create_file(const std::string &filename) {
    std::ofstream target(filename.c_str());
    target.close();
}
