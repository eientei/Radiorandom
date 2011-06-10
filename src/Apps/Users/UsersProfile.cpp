#include <Apps/Server.h>

void controller::users_profile() {
	model::users_profile c;
	prepare(c,menu_item("[Profile]","/users/profile"));
	render("html_users_profile",c);
}
