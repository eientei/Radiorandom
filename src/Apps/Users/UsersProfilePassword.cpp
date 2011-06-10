#include <Apps/Server.h>

void controller::users_profile_password() {
	model::users_profile_password c;
	prepare(c,menu_item("[Profile]","/users/profile"));
	
	if(request().request_method()=="POST") {
		c.load(context());
		if (!c.validate()) {
			render("html_users_profile_password",c);
			return;
		}
		string hash = sha1hash_buf(c.password.value());
		c.message = "Successfuly changed password";
		cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
		radiorandom_sql << "update users set password_hash = ? where id = (select id from sessions where hash = ?)" << hash <<  request().cookie_by_name("session").value() << cppdb::exec;
	}
	render("html_users_profile_password",c);
}
