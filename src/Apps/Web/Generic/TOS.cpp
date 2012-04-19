#include "../Web.h"

void Web::TOS(std::string skin) {
	if (skin.empty()) skin = default_skin;
	Models::Generic::TOS c;
	Prepare(c,"[TOS]");
	render(skin,"TOS",c);
}
