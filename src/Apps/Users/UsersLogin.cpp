#include <Apps/Server.h>

void controller::users_login() {
	model::users_login c;
	prepare(c,menu_item("[Login]","/users/login"));
	if(request().request_method()=="POST") {
		c.load(context());
		if (c.validate()) {
			response().set_redirect_header("/");
			string session = make_session(c.username.value());
			response().set_cookie(cppcms::http::cookie::cookie("session",session,60*60*24*31*12,"/","radiorandom.neverb.net"));
			return;
		}
	}
	render("html_users_login",c);
}
