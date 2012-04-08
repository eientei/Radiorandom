#ifndef DATA_USER_HPP
#define DATA_USER_HPP

#include <string>
#include <vector>

namespace data {
    struct user {
            std::string name;
            std::string password_hash;
            std::string email;
            std::vector<std::string> groups;
            std::vector<std::string> rights;
            bool logged_in;

            user()
                : logged_in(false)
            { }
    };
}

#endif // DATA_USER_HPP
