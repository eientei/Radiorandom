#include <Apps/Server.h>

void controller::users_show(string strid) {
	model::users_show c;
	prepare(c,menu_item("[Users]","/users"));
	int id;
	sscanf(strid.c_str(),"%d",&id);
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result users = radiorandom_sql << "select * from users where id = ?" << id;
	if (users.next()) {
		c.id = id;
		c.username = users.get<string>("username");
		c.score = users.get<int>("score");
		c.access = users.get<int>("access");
		c.joined = users.get<int>("joined");
	}
	render("html_users_show",c);
}
