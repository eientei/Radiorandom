#include "Server.h"

std::string radio_random::valid_user_cookie() {
	std::string session = request().cookie_by_name("session").value();
	
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result users = radiorandom_sql << "select username from sessions left join users on users.id = id where hash = ?" << session;
	if (!users.next()) return "";
	return users.get<std::string>("username");
}

void radio_random::set_menu(radiorandom::menu &c, menu_item current, bool login) {
	bool emergency = false;
	
	struct stat filestatus;
	std::string setuplock = settings().get<std::string>("setup.lockfile");
	stat(setuplock.c_str(), &filestatus);
	if (!S_ISREG(filestatus.st_mode)) {
		emergency = true;
	}

	c.menu_current = current;
	
	c.menu_links_left.push_back(menu_item("[Index]","/"));
	c.menu_links_left.push_back(menu_item("[Playlist]","/playlist"));
	c.menu_links_left.push_back(menu_item("[Users]","/users"));
	std::string username;
	if (emergency || (username = valid_user_cookie()).length() || login) {
		c.logined = true;
		c.username = username;
		c.menu_links_right.push_back(menu_item("[Home]","/users/profile"));
		if (emergency) {
			c.menu_links_right.push_back(menu_item("[Setup]","/setup"));
		} else {
			c.menu_links_right.push_back(menu_item("[Logout]","/users/logout"));
		}
	} else {
		c.menu_links_right.push_back(menu_item("[Register]","/users/new"));
		c.menu_links_right.push_back(menu_item("[Login]","/users/login"));
	}
	c.menu_links_right.push_back(menu_item("[TOS]","/tos"));
}
radio_random::radio_random(cppcms::service &srv) :
	cppcms::application(srv)
{
	dispatcher().assign("/",&radio_random::index,this);
	dispatcher().assign("/setup",&radio_random::setup,this);
	dispatcher().assign("/tos",&radio_random::tos,this);
	dispatcher().assign("/users($|\\?.*)",&radio_random::users,this);
	dispatcher().assign("/users/([0-9]*)",&radio_random::users_show,this,1);
	dispatcher().assign("/users/new",&radio_random::users_new,this);
	dispatcher().assign("/users/logout",&radio_random::users_logout,this);
	dispatcher().assign("/users/login",&radio_random::users_login,this);
	dispatcher().assign("/users/profile",&radio_random::users_profile,this);
	dispatcher().assign("/users/profile/password",&radio_random::users_profile_password,this);
	dispatcher().assign("/users/profile/settings",&radio_random::users_profile_settings,this);
}

void radio_random::tos() {
	radiorandom::tos c;
	set_menu(c,menu_item("[TOS]","/tos"));
	render("html_tos",c);
}
void radio_random::setup() {
	radiorandom::setup c;
	set_menu(c,menu_item("[Setup]","/setup"));
	
	std::string setuplock = settings().get<std::string>("setup.lockfile");
	struct stat filestatus;
	stat(setuplock.c_str(), &filestatus);
	if (S_ISREG(filestatus.st_mode)) {
		c.already_setted_up = true;
		render("html_setup",c);
		return;
	}
	if(request().request_method()=="POST") {
		c.load(context());
		c.clear();
		FILE *fp = fopen(setuplock.c_str(),"w");
		fclose(fp);
		std::string users_schema = settings().get<std::string>("db-schema.users");
		std::string files_schema = settings().get<std::string>("db-schema.files");
		std::string sessions_schema = settings().get<std::string>("db-schema.sessions");
		cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
		radiorandom_sql << "drop table if exists users" << cppdb::exec;
		radiorandom_sql << "drop table if exists sessions" << cppdb::exec;
		radiorandom_sql << "drop table if exists files" << cppdb::exec;
		radiorandom_sql << users_schema << cppdb::exec;
		radiorandom_sql << sessions_schema << cppdb::exec;
		radiorandom_sql << files_schema << cppdb::exec;
		response().set_redirect_header("/");
	}
	render("html_setup",c);
}	
void radio_random::index() {
	radiorandom::index c;
	
	set_menu(c,menu_item("[Index]","/"));
	
	c.files = 0;
	c.filessize = 0;
	
	
	render("html_index",c);
}
void radio_random::main(std::string url) {
	radiorandom::error c;
	if (url != "/setup") {
		struct stat filestatus;
		std::string setuplock = settings().get<std::string>("setup.lockfile");
		stat(setuplock.c_str(), &filestatus);
		if (!S_ISREG(filestatus.st_mode)) {
			set_menu(c);
			response().set_redirect_header("/setup");
			return;
		}
	}
	if (!dispatcher().dispatch(url)) {
		set_menu(c);
		c.errorcode = 404;
		render("html_error",c);
	}
}

int main(int argc, char **argv) {
	printf("Server fired up\n");
	pio_init();
	try {
		cppcms::service srv(argc,argv);
		srv.applications_pool().mount(cppcms::applications_factory<radio_random>());
		srv.run();
	} catch(std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}
}
