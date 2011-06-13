#ifndef RADIORANDOM_MODELS_MASTER_MENU
#define RADIORANDOM_MODELS_MASTER_MENU

#include <radiorandom/data/content/menu_set.h>
#include <radiorandom/models/master/generic.h>

namespace models {
namespace master {
	struct menu :public models::master::generic {
		data::content::menu_set menu_left;
		data::content::menu_set menu_right;
		data::content::menu_set submenu_left;
		data::content::menu_set submenu_right;
		data::content::menu_item menu_current;
		data::content::menu_item submenu_current;
		bool is_submenu;
		menu(){
			is_submenu = false;
		}
	};
}
}


#endif
