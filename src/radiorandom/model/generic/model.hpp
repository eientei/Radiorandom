#ifndef MODEL_GENERIC_HPP
#define MODEL_GENERIC_HPP

#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include <cppcms/view.h>

#include <radiorandom/data/user/data.hpp>

namespace content {
    struct generic : public cppcms::base_content {
            bool  is_installed;

            std::string site_name;

            std::string menu_item;
            std::string submenu_item;

            std::map<std::string,std::string> menu_items;
            std::map<std::string,std::string> submenu_items;

            data::user user;

            bool in_group(std::string group) {
                return std::find(user.groups.begin(),user.groups.end(),group) != user.groups.end();
            }

            bool has_right(std::string right) {
                return std::find(user.rights.begin(),user.rights.end(),right) != user.rights.end();
            }
    };
}


#endif // MODE_GENERICL_HPP
