#include "Server.h"
void radio_random::users_profile_settings() {
	radiorandom::users_profile_settings c;
	set_menu(c,menu_item("[Home]","/users/profile"));
	render("html_users_profile_settings",c);
}

void radio_random::users_profile_password() {
	radiorandom::users_profile_password c;
	set_menu(c,menu_item("[Home]","/users/profile"));
	if(request().request_method()=="POST") {
		c.load(context());
		if (c.validate()) {
			c.message = "Successfuly changed password.";
			cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
			std::string hash = sha1hash(c.password.value().c_str());
			
			radiorandom_sql << "update users set password_hash = ? where id = (select id from sessions where hash = ?)" << hash <<  request().cookie_by_name("session").value() << cppdb::exec;
		}
	}
	render("html_users_profile_password",c);	
}

void radio_random::users_profile() {
	radiorandom::users_profile c;
	set_menu(c,menu_item("[Home]","/users/profile"));
	render("html_users_profile",c);	
}

void radio_random::users_new() {
	radiorandom::users_new c;
	bool login = false;
	if(request().request_method()=="POST") {
		c.load(context());
		if (c.validate()) {
			cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
			cppdb::result users = radiorandom_sql << "select count(*) from users where username = ?" << c.username.value();
			users.next();
			if (users.get<int>(0) == 0) {
				c.result = true;
				login = true;
				users.next();
				std::string hash = sha1hash(c.password.value().c_str());
				radiorandom_sql << "insert into users values (NULL,?,?,0,0,strftime('%s','now'))" << c.username.value() << hash << cppdb::exec;


				std::string session = make_session(c.username.value());
								
				response().set_cookie(cppcms::http::cookie::cookie("session",session,60*60*24*31*12,"/","radiorandom.neverb.net"));
			} else {
				c.username_message += " already exists";
				c.result = false;
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
	std::string stroffset = getreq.find("page")->second;
	int offset = 0;
	sscanf(stroffset.c_str(),"%d",&offset);
	
	if (sortby != "score" && sortby != "access" && sortby != "username")
		sortby = "joined";
	if (direction != "asc")
		direction = "desc";
		
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result users;
	int userslimit = settings().get<int>("limits.users");
	users = radiorandom_sql << "select count(*) from users";
	users.next();
	int userscount = users.get<int>(0);
	int page = (offset - 1) * userslimit;
	if (page < 0) page = 0;
		c.prefix = "?sortby=" + sortby + "&amp;direction=" + direction;
	if (userscount > userslimit) {
		c.many = true;
		c.page = offset;
		c.total = userscount;
		c.pagesize = userslimit;
		char buf[1024];
		snprintf(buf,1024,"%d",page + 1);
		c.suffix="&page=" + std::string(buf);
	}
	users = radiorandom_sql << "select * from users order by " + sortby + " " + direction + " limit ? offset ?" << userslimit << page;
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
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result users;
	users = radiorandom_sql << "select * from users where id = ?" << uid;
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
		std::string password_hash = sha1hash(password.c_str());
		if (valid_user(username,password_hash)) {
			response().set_redirect_header("/");
			std::string session = make_session(c.username.value());
								
			response().set_cookie(cppcms::http::cookie::cookie("session",session,60*60*24*31*12,"/","radiorandom.neverb.net"));
			return;
		} else {
			c.message = "Wrong login/password.";
		}
	}
	render("html_users_login",c);
	
}
void radio_random::users_logout() {
	response().set_redirect_header("/");
	std::string hash = request().cookie_by_name("session").value();
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	radiorandom_sql << "delete from sessions where hash = ?" << hash << cppdb::exec;
	response().set_cookie(cppcms::http::cookie::cookie("session","",0,"/","radiorandom.neverb.net"));
}
