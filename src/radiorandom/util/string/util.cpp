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

std::string util::string::replaceAll(std::string source, std::string const& from, std::string const& to) {
    size_t index = 0;
    while ((index = source.find(from,index)) != std::string::npos) {
        source.replace(index,from.length(),to);
        index += to.length();
    }
    return source;
}

std::string util::string::saltify(std::string const& salt, std::string const& password) {
    return replaceAll(salt,"%s",password);
}


std::string util::string::sha1hash(std::string const& input) {
    char out[41];
    unsigned char md[20];
    SHA1((const unsigned char*)input.c_str(),input.length(),md);
    for (int i = 0; i < 20; i++) {
        snprintf(&out[i*2],3,"%02x",md[i]);
    }
    return out;
}
