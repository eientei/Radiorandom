#include <Apps/Server.h> 

void controller::setup() {
	model::setup c;
	prepare(c,menu_item("[Setup]","/setup"));
	if(request().request_method()=="POST") {
		c.load(context());
		c.clear();
		string setuplock = settings().get<std::string>("setup.lockfile");
		FILE *fp = fopen(setuplock.c_str(),"w");
		fclose(fp);
		std::string users_schema = settings().get<std::string>("db-schema.users");
		std::string posts_schema = settings().get<std::string>("db-schema.posts");
		std::string sessions_schema = settings().get<std::string>("db-schema.sessions");
		std::string anons_schema = settings().get<std::string>("db-schema.anons");
		std::string votes_schema = settings().get<std::string>("db-schema.votes");
		
		cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
		radiorandom_sql << "drop table if exists users" << cppdb::exec;
		radiorandom_sql << "drop table if exists sessions" << cppdb::exec;
		radiorandom_sql << "drop table if exists posts" << cppdb::exec;
		radiorandom_sql << "drop table if exists anons" << cppdb::exec;
		radiorandom_sql << "drop table if exists votes" << cppdb::exec;
		radiorandom_sql << users_schema << cppdb::exec;
		radiorandom_sql << sessions_schema << cppdb::exec;
		radiorandom_sql << posts_schema << cppdb::exec;
		radiorandom_sql << anons_schema << cppdb::exec;
		radiorandom_sql << votes_schema << cppdb::exec;
		response().set_redirect_header("/");
		
	}
	render("html_setup",c);
}
