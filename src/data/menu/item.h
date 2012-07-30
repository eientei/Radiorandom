#ifndef DATA_MENU_ITEM_H
#define DATA_MENU_ITEM_H

namespace data {
namespace menu {
struct item  {
    item(const std::string &name, const std::string &id)
        : name(name), id(id)
    {

    }

    std::string name;
    std::string id;
};
} // namespace post
}

#endif // DATA_MENU_ITEM_H

