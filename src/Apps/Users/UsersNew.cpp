#include <Apps/Server.h>

void controller::users_new() {
	model::users_new c;
	bool login;
	if(request().request_method()=="POST") {
		c.load(context());
		if (!c.validate()) {
			prepare(c,menu_item("[Register]","/users/new"));
			render("html_users_new",c);
			return;
		}
		string hash = sha1hash_buf(c.password.value().c_str());
		cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
		radiorandom_sql << "insert into users values (NULL,?,?,10,1,?,strftime('%s','now'),strftime('%s','now'))" << c.username.value() << hash << c.email.value() << cppdb::exec;
		string session = make_session(c.username.value());
		response().set_cookie(cppcms::http::cookie::cookie("session",session,60*60*24*31*12,"/"));
		login = true;
	}
	prepare(c,menu_item("[Register]","/users/new"),login);
	render("html_users_new",c);
}
