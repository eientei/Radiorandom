#ifndef RADIORANDOM_HELPERS_NAVIGATION
#define RADIORANDOM_HELPERS_NAVIGATION

/// @file

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <radiorandom/models/master/menu.h>
#include <radiorandom/data/content/menu_set.h>

namespace helpers {
	class navigation {
		public:
			static std::string navgen_helper(int begin, int end, int page, int pagesize, std::string prefix, std::string infix, int pn=1);
			static std::string generator(int page, int total, int pagesize, std::string prefix, std::string infix);
			static void gen_menu(models::master::menu &c,data::content::menu_item current, bool login = false, data::content::menu_item submenu_current = data::content::menu_item());
	};
}

#endif
