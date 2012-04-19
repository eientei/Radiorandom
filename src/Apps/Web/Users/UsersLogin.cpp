#include "../Web.h"

void Web::UsersLogin(std::string skin) {
	if (skin.empty()) skin = default_skin;
	Models::Users::UsersLogin c;
	Prepare(c,"[Login]");
	if(request().request_method()=="POST") {
		c.load(context());
		if (c.validate()) {
			response().set_redirect_header("/");
			std::string session = Generic::DB::Users().MakeSession(c.username.value());
			response().set_cookie(cppcms::http::cookie::cookie("session",session,60*60*24*31*12,"/"));
			return;
		}
	}
	
	
	render(skin,"UsersLogin",c);
}

