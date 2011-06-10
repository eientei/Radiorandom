#include <Apps/Server.h>

void controller::users_profile_email() {
	model::users_profile_email c;
	prepare(c,menu_item("[Profile]","/users/profile"));
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	if (c.user_auth) {
		cppdb::result email = radiorandom_sql << "select email from users where id = (select id from sessions where hash = ?)" << request().cookie_by_name("session").value();
		email.next();
		c.current_email = email.get<string>("email");
	} else {
		c.current_email = "Are you even registered, little bugger?";
	}
	if(request().request_method()=="POST") {
		c.load(context());
		if (!c.validate()) {
			render("html_users_profile_email",c);
			return;
		}
		c.message = "Successfuly changed email";
		c.current_email = c.email.value();
		radiorandom_sql << "update users set email = ? where id = (select id from sessions where hash = ?)" << c.email.value() <<  request().cookie_by_name("session").value() << cppdb::exec;
	}
	render("html_users_profile_email",c);
}
