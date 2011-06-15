#include "Menu.h"

Generic::Markup::Menu::Menu(Models::Master::Menu &c, std::string current, std::string submenu_current, bool login) {
	typedef Generic::Data::Content::SetMenu::ItemMenu ItemMenu;
	c.menu_current = ItemMenu(current,"/");
	if (!c.generic_setted_up) {
		c.menu_right.AddItem(ItemMenu("[Setup]","/"));
		return;
	}

	c.menu_left.AddItem(ItemMenu("[Index]","/"));
	c.menu_left.AddItem(ItemMenu("[Posts]","/posts"));
	c.menu_left.AddItem(ItemMenu("[Users]","/users"));
	if (c.user.authed || login) {
		c.menu_right.AddItem(ItemMenu("[Profile]","/users/profile"));
		c.menu_right.AddItem(ItemMenu("[Logout]","/users/logout"));
	} else {
		c.menu_right.AddItem(ItemMenu("[Register]","/users/register"));
		c.menu_right.AddItem(ItemMenu("[Login]","/users/login"));
	}
	c.menu_right.AddItem(ItemMenu("[TOS]","/tos"));
	if (current== "[Posts]") {
		c.submenu_current = ItemMenu(submenu_current,"/");
		c.submenu_left.AddItem(ItemMenu("[Index]","/posts"));
		c.submenu_left.AddItem(ItemMenu("[Upload]","/posts/new"));
		c.submenu_left.AddItem(ItemMenu("[Search]","/posts/search"));
	} else if (current == "[Users]") {
		c.submenu_current = ItemMenu(submenu_current,"/");
		c.submenu_left.AddItem(ItemMenu("[Index]","/users"));
		c.submenu_left.AddItem(ItemMenu("[My Profile]","/users/" + format.ToString(c.user.id)));
		c.submenu_left.AddItem(ItemMenu("[Search]","/users/search"));
	}
	
}
