#include "../Web.h"

void Web::MakeError(std::string skin, int error_code, std::string error_message) {
	if (skin.empty()) skin = default_skin;
	Models::Generic::Error c;
	Prepare(c,"[Error]");
	c.error_code = error_code;
	c.error_message = error_message;
	render(skin,"Error",c);
}
