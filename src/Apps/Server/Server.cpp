#include "Server.h"

bool radio_random::valid_user_cookie() {
	std::string username = request().cookie_by_name("username").value();
	std::string password_hash = request().cookie_by_name("password_hash").value();
	return valid_user(username,password_hash);
}

void radio_random::set_menu(radiorandom::menu &c, menu_item current, bool login) {
	c.menu_current = current;
	
	c.menu_links_left.push_back(menu_item("[Index]","/"));
	c.menu_links_left.push_back(menu_item("[Playlist]","/playlist"));
	c.menu_links_left.push_back(menu_item("[Users]","/users"));
	
	if (valid_user_cookie() || login) {
		c.menu_links_right.push_back(menu_item("[Home]","/users/profile"));
		c.menu_links_right.push_back(menu_item("[Logout]","/users/logout"));
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
}

void radio_random::tos() {
	radiorandom::tos c;
	set_menu(c,menu_item("[TOS]","/tos"));
	render("html_tos",c);
}
void radio_random::setup() {
	radiorandom::setup c;
	set_menu(c);
	
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
		cppdb::session users_sql("sqlite3:db=db/users.db");
		cppdb::session files_sql("sqlite3:db=db/files.db");
		users_sql << "drop table users" << cppdb::exec;
		files_sql << "drop table files" << cppdb::exec;
		users_sql << users_schema << cppdb::exec;
		files_sql << files_schema << cppdb::exec;
	}
	render("html_setup",c);
}	
void radio_random::index() {
	radiorandom::index c;
	
	set_menu(c,menu_item("[Index]","/"));
	
	c.files = 0;
	c.filessize = 0;
	
	try {
		cppdb::session sql("sqlite3:db=db/files.db");
	} catch (std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}
	
	render("html_index",c);
}
void radio_random::main(std::string url) {
	if (!dispatcher().dispatch(url)) {
		radiorandom::error c;
		
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
