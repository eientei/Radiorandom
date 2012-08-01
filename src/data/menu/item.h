#ifndef DATA_MENU_ITEM_H
#define DATA_MENU_ITEM_H

#include <string>

namespace data {
namespace menu {
struct item  {
    item()
    {
        m_empty = true;
    }

    item(const std::string &a_name, const std::string &a_id, const item &parent = item())
        : name(a_name), orig_id(a_id), m_empty(false)
    {
        if (parent.m_empty == true) {
            id = a_id;
        } else {
            id   = parent.id   + "_" + a_id;
            path = parent.path + "/" + a_id;
        }
    }

    std::string name;
    std::string id;
    std::string path;
    std::string orig_id;
private:
    bool m_empty;
};
} // namespace post
}

#endif // DATA_MENU_ITEM_H

