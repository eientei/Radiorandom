#include <Apps/Server.h>

void controller::users_profile_settings() {
	model::users_profile_settings c;
	prepare(c,menu_item("[Profile]","/users/profile"));
	render("html_users_profile_settings",c);
}
