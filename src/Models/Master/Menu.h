#ifndef MODELS_MASTER_MENU
#define MODELS_MASTER_MENU

/// @file

#include <Models/Master/Generic.h>
#include <Generic/Data/Content/SetMenu/SetMenu.h>

namespace Models {
	namespace Master {
		/// Menu struct.
		/// Indirectly used everywhere through Master struct.
		struct Menu : public Models::Master::Generic {
			::Generic::Data::Content::SetMenu menu_left;        ///< Menu set right
			::Generic::Data::Content::SetMenu menu_right;       ///< Menu set left
			::Generic::Data::Content::SetMenu submenu_left;     ///< Submenu set left
			::Generic::Data::Content::SetMenu submenu_right;    ///< Submenu set right
			::Generic::Data::Content::SetMenu::ItemMenu menu_current;    ///< Current menu link
			::Generic::Data::Content::SetMenu::ItemMenu submenu_current; ///< Current submenu link
		};
	}
}


#endif
