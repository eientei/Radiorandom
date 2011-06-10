#include <Helpers/Navigation/Menu.h>

void gen_menu(model::menu &c, menu_item current, bool login) {
	c.menu_current = current;
	if (c.setted_up == false) {
		c.menu_links_right.push_back(menu_item("[Setup]","/setup"));
		return;
	}
	c.menu_links_left.push_back(menu_item("[Index]","/"));
	c.menu_links_left.push_back(menu_item("[Posts]","/posts"));
	c.menu_links_left.push_back(menu_item("[Users]","/users"));
	if ((c.user_auth == true) || login) {
		c.menu_links_right.push_back(menu_item("[Profile]","/users/profile"));
		c.menu_links_right.push_back(menu_item("[Logout]","/users/logout"));
	} else {
		c.menu_links_right.push_back(menu_item("[Register]","/users/new"));
		c.menu_links_right.push_back(menu_item("[Login]","/users/login"));
	}
	c.menu_links_right.push_back(menu_item("[TOS]","/tos"));
}
