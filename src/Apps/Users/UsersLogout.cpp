#include <Apps/Server.h>

void controller::users_logout() {
	response().set_redirect_header("/");
	std::string hash = request().cookie_by_name("session").value();
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	radiorandom_sql << "delete from sessions where hash = ?" << hash << cppdb::exec;
	response().set_cookie(cppcms::http::cookie::cookie("session","",0,"/","radiorandom.neverb.net"));
}
