#include "../Web.h"

void Web::UsersProfileSettings(std::string skin) {
	if (skin.empty()) skin = default_skin;
	Models::Users::UsersProfileSettings c;
	Prepare(c,"[Profile]");
	render(skin,"UsersProfileSettings",c);
}


