#include "../Web.h"

void Web::UsersLogout(std::string skin) {
	if (skin.empty()) skin = default_skin;
	Models::Users::UsersLogout c;
	Prepare(c,"[Logout]");
	std::string session = GetFromCookie("session");
	Generic::DB::Users().DeleteSession(session);
	response().set_cookie(cppcms::http::cookie::cookie("session",session,0,"/"));
	response().set_redirect_header("/");
	render(skin,"UsersLogout",c);
}

