#include "../Web.h"

void Web::UsersProfileEmail(std::string skin) {
	if (skin.empty()) skin = default_skin;
	Models::Users::UsersProfileEmail c;
	Prepare(c,"[Profile]");
	if (!c.user.authed) {
		MakeError(skin,403,"Accessd denied");
		return;
	}
	if(request().request_method()=="POST") {
		c.load(context());
		if (!c.validate()) {
			render(skin,"UsersProfileEmail",c);
			return;
		}
		if (c.user.authed) {
			c.success_message = "Successfuly changed email";
			Generic::DB::Users().ChangeEmail(c.user.id, c.user.id, c.email.value());
			c.user.email = c.email.value();
			
		}
	}
	render(skin,"UsersProfileEmail",c);
}



