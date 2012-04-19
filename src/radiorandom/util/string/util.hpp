#ifndef UTIL_STRING_HPP
#define UTIL_STRING_HPP

#include <sstream>
#include <string>

#include <stdio.h>

#include <openssl/sha.h>



namespace util {
    namespace string {
        std::string to_string(int num);
        std::string to_string(bool boolean);
        std::string replaceAll(std::string source, std::string const& from, std::string const& to);
        std::string saltify(std::string const& salt, std::string const& password);
        std::string sha1hash(std::string const& input);
    }
}


#endif // UTIL_STRING_HPP
