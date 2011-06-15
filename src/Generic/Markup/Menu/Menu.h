#ifndef GENERIC_MARKUP_MENU
#define GENERIC_MARKUP_MENU
/// @file


#include <Models/Master/Menu.h>
#include <Generic/Generic.h>
#include <Generic/Data/Content/SetMenu/SetMenu.h>
#include <Generic/Data/Format/Format.h>

/// Menu filler
class Generic::Markup::Menu {
	public:
		Generic::Data::Format format; ///< Formatter object
		Menu() {}
		/// Usual constructor
		Menu(Models::Master::Menu &c, std::string current, std::string submenu_current = "", bool login = false);
};


#endif
