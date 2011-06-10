#include <Helpers/Auth/ValidSession.h>

///@file


string valid_session(string session) {
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result users = radiorandom_sql << "select username from sessions left join users on users.id = id where hash = ?" << session;
	if (!users.next()) return "";
	return users.get<std::string>("username");
}

