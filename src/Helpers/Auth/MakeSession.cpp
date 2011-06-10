#include <Helpers/Auth/MakeSession.h>

string make_session(string username) {
	time_t rawtime;
	struct tm * timeinfo;
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result users = radiorandom_sql << "select id from users where username = ?;" << username;
	
	int id;
	while (users.next()) {
		id = users.get<int>("id");
	}
	users.clear();
	char buf[1024];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buf,1024,"%c",timeinfo);
	std::string hash = sha1hash_buf(buf);
	radiorandom_sql << "insert into sessions values (?,?,strftime('%s','now'));" << hash << id << cppdb::exec;
	return hash;
}
