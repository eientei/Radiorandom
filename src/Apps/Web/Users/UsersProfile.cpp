#include "../Web.h"

void Web::UsersProfile(std::string skin) {
	if (skin.empty()) skin = default_skin;
	Models::Users::UsersProfile c;
	Prepare(c,"[Profile]");
	render(skin,"UsersProfile",c);
}


