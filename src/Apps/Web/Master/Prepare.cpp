#include "../Web.h"

void Web::Prepare(Models::Master::Master &c, std::string current, std::string submenu_current, bool login) {
	std::string lock = GetFromConfig<std::string>("setup.lockfile");
	if (Generic::FileSystem::Check(lock).ExistFile()) {
		c.generic_setted_up = true;
		std::string session = GetFromCookie("session");
		Generic::DB::Users().AuthUser(c,session);
	}
	Generic::Markup::Menu(c,current,submenu_current,login);
}
