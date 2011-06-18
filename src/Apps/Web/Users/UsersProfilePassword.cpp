#include "../Web.h"

void Web::UsersProfilePassword(std::string skin) {
	if (skin.empty()) skin = default_skin;
	Models::Users::UsersProfilePassword c;
	Prepare(c,"[Profile]");
	if (!c.user.authed) {
		MakeError(skin,403,"Accessd denied");
		return;
	}
	if(request().request_method()=="POST") {
		c.load(context());
		if (!c.validate()) {
			render(skin, "UsersProfilePassword",c);
			return;
		}
		c.message = "Successfuly changed password";
		Generic::DB::Users().ChangePassword(c.user.id, c.user.id, c.password.value());
	}
	render(skin,"UsersProfilePassword",c);
}



