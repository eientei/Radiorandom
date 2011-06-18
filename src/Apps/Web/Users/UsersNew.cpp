#include "../Web.h"

void Web::UsersNew(std::string skin) {
	if (skin.empty()) skin = default_skin;
	Models::Users::UsersNew c;
	std::string lock = GetFromConfig<std::string>("setup.lockfile");
	if (Generic::FileSystem::Check(lock).ExistFile()) {
		c.generic_setted_up = true;
		std::string session = GetFromCookie("session");
		Generic::DB::Users().AuthUser(c,session);
	}
	if (c.user.authed) {
		MakeError(skin,403,"Access denied");
		return;
	}
	bool login = false;
	if(request().request_method()=="POST") {
		c.load(context());
		if (!c.validate()) {
			Prepare(c,"[Register]");
			render(skin,"UsersNew",c);
			return;
		}
		login = true;
		Generic::DB::Users users;
		users.CreateUser(
			c.username.value(),
			c.password.value(),
			c.email.value(),
			false
		);
		std::string session = users.MakeSession(c.username.value());
		response().set_cookie(cppcms::http::cookie::cookie("session",session,60*60*24*31*12,"/"));
	}
	Prepare(c,"[Register]","",login);
	render(skin,"UsersNew",c);	
}
