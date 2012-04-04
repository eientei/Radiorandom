#ifndef SQL_HPP
#define SQL_HPP

#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include <openssl/sha.h>

namespace util {
    namespace sql {
        std::string salt_password(std::string const& salt, std::string const& raw_password);
        std::string hash_password(std::string const& password);
        std::string make_password_hash(std::string const& salt, std::string const& raw_password);

        bool add_user(std::string const& name, std::string const& salt, std::string const& password, std::string const& email);
    }
}

#endif // SQL_HPP
