#include "util.hpp"


std::string util::string::to_string(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

std::string util::string::to_string(bool boolean) {
    if (boolean) {
        return "true";
    } else {
        return "false";
    }
}
