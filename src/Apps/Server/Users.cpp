#include "Server.h"

void radio_random::users_new() {
	radiorandom::users_new c;
	bool login = false;
	if(request().request_method()=="POST") {
		c.load(context());
		if (c.validate()) {
			cppdb::session users_sql("sqlite3:db=db/users.db");
			cppdb::result users = users_sql << "select count(*) from users where username = ?" << c.username.value();
			users.next();
			if (users.get<int>(0) == 0) {
				c.result = true;
				login = true;
				char *hash = sha1hash(c.password.value().c_str());
				users_sql << "insert into users values (NULL,?,?,0,0,strftime('%s','now'))" << c.username.value() << hash << cppdb::exec;
				response().set_cookie(cppcms::http::cookie::cookie("username",c.username.value(),60*60*24*31*12,"/","radiorandom.neverb.net"));
				response().set_cookie(cppcms::http::cookie::cookie("password_hash",hash,60*60*24*31*12,"/","radiorandom.neverb.net"));
				delete[] hash;
			} else {
				c.username_message += " already exists";
			}
		}
	}
	set_menu(c,menu_item("[Register]","/users/new"),login);
	render("html_users_new",c);	
}
void radio_random::users() {
	radiorandom::users c;
	set_menu(c,menu_item("[Users]","/users"));
	
	std::multimap<std::string,std::string> getreq = request().get();
	
	std::string sortby = getreq.find("sortby")->second;
	std::string direction = getreq.find("direction")->second;
	
	if (sortby != "score" && sortby != "access" && sortby != "username")
		sortby = "joined";
	if (direction != "asc")
		direction = "desc";
		
	cppdb::session users_sql("sqlite3:db=db/users.db");
	cppdb::result users;
	users = users_sql << "select * from users order by " + sortby + " " + direction;
	while (users.next()) {
		std::string un = users.get<std::string>("username");
		int id = users.get<int>("id");
		int score = users.get<int>("score");
		int access = users.get<int>("access");
		int joined = users.get<int>("joined");
		c.usersset.push_back(user_item(id,un,score,access,joined));
	}
	
	if (sortby == "username") {
		if (direction == "asc") direction = "desc";
		else direction = "asc";
		c.sort_username_dir = direction;
	}
	if (sortby == "score") {
		if (direction == "asc") direction = "desc";
		else direction = "asc";
		c.sort_score_dir = direction;
	}
	if (sortby == "access") {
		if (direction == "asc") direction = "desc";
		else direction = "asc";
		c.sort_access_dir = direction;
	}
	if (sortby == "joined") {
		if (direction == "asc") direction = "desc";
		else direction = "asc";
		c.sort_joined_dir = direction;
	}
			
	render("html_users",c);	
}
void radio_random::users_show(std::string id) {
	radiorandom::users_show c;
	set_menu(c,menu_item("[Users]","/users"));
	int uid;
	sscanf(id.c_str(),"%d",&uid);
	cppdb::session users_sql("sqlite3:db=db/users.db");
	cppdb::result users;
	users = users_sql << "select * from users where id = ?" << uid;
	if (users.next()) {
		std::string un = users.get<std::string>("username");
		int id = users.get<int>("id");
		int score = users.get<int>("score");
		int access = users.get<int>("access");
		int joined = users.get<int>("joined");
		c.user = user_item(id,un,score,access,joined);
	}
	render("html_users_show",c);
}
void radio_random::users_login() {
	radiorandom::users_login c;
	set_menu(c,menu_item("[Login]","/users/login"));
	if(request().request_method()=="POST") {
		c.load(context());
		std::string username = c.username.value();
		std::string password = c.password.value();
		char *password_hash = sha1hash(password.c_str());
		if (valid_user(username,password_hash)) {
			response().set_redirect_header("/");
			response().set_cookie(cppcms::http::cookie::cookie("username",username,60*60*24*31*12,"/","radiorandom.neverb.net"));
			response().set_cookie(cppcms::http::cookie::cookie("password_hash",password_hash,60*60*24*31*12,"/","radiorandom.neverb.net"));
			return;
		} else {
			c.message = "Wrong login/password.";
		}
		delete[] password_hash;
	}
	render("html_users_login",c);
	
}
void radio_random::users_logout() {
	response().set_redirect_header("/");
	response().set_cookie(cppcms::http::cookie::cookie("username","",0,"/","radiorandom.neverb.net"));
	response().set_cookie(cppcms::http::cookie::cookie("password_hash","",0,"/","radiorandom.neverb.net"));
}
