#ifndef MODEL_GENERIC_HPP
#define MODEL_GENERIC_HPP

#include <string>

#include <cppcms/view.h>

namespace content {
    struct generic : public cppcms::base_content {
            bool is_installed;
            std::string menu_item;
            std::string submenu_item;
    };
}

#endif // MODEL_GENERIC_HPP
