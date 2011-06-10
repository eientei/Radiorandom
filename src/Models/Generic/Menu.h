#ifndef RADIORANDOM_MODELS_GENERIC_MENU
#define RADIORANDOM_MODELS_GENERIC_MENU

/// @file

#include <Data/MenuSet/MenuSet.h>


namespace model {

	/// Menu model
	struct menu :public auth {
		menu_set menu_links_left;     ///< left side of submenu links
		menu_set menu_links_right;    ///< right side of menu links
		menu_set submenu_links_left;  ///< left side of submenu links
		menu_set submenu_links_right; ///< right side of submenu links
		menu_item menu_current;       ///< current menu item
		menu_item submenu_current;    ///< current submenu item
	};
}
#endif

