#ifndef MODEL_GENERIC_HPP
#define MODEL_GENERIC_HPP

#include <string>
#include <map>
#include <vector>

#include <cppcms/view.h>

namespace content {
    struct generic : public cppcms::base_content {
            bool is_installed;
            std::string menu_item;
            std::string submenu_item;

            std::map<std::string,std::string> menu_items;
            std::map<std::string,std::string> submenu_items;

            std::string user_name;
            std::string user_password_hash;
            std::string user_email;
            std::vector<std::string> user_groups;
            std::vector<std::string> user_rights;
            bool user_logged_in;

            generic() : user_logged_in(false) { }

            bool in_group(std::string group) {
                for (std::vector<std::string>::const_iterator it = user_groups.begin(); it != user_groups.end(); it++) {
                    if (*it == group) {
                        return true;
                    }
                }
                return false;
            }

            bool has_right(std::string right) {
                for (std::vector<std::string>::const_iterator it = user_rights.begin(); it != user_rights.end(); it++) {
                    if (*it == right) {
                        return true;
                    }
                }
                return false;
            }
    };
}

#endif // MODEL_GENERIC_HPP
