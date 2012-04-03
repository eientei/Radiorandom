#ifndef MODEL_GENERIC_HPP
#define MODEL_GENERIC_HPP

#include <string>
#include <map>

#include <cppcms/view.h>

namespace content {
    struct generic : public cppcms::base_content {
            bool is_installed;
            std::string menu_item;
            std::string submenu_item;

            std::map<std::string,std::string> menu_items;
            std::map<std::string,std::string> submenu_items;
    };
}

#endif // MODEL_GENERIC_HPP
