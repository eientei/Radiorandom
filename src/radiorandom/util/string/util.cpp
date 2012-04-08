#include "util.hpp"


std::string util::string::to_string(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}
