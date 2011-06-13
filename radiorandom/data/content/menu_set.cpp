#include <radiorandom/data/content/menu_set.h>

data::content::menu_item::menu_item() {
}
data::content::menu_item::menu_item(
	std::string name, 
	std::string href
) :
	name(name),
	href(href)
{}
