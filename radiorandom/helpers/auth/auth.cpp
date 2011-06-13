                                      #include <radiorandom/helpers/auth/auth.h>

/// @file

void helpers::auth::auth_user(models::master::generic &c, std::string session) {
	if (helpers::auth::session_exist(session)) {
		db::result users = db::sql() << "select users.name,users.id,users.access from sessions left join users on users.id = userid where hash = ?" << session;
		users.next();
		c.user_authed = true;
		c.user_name = users.get<std::string>("username");
		c.user_id = users.get<int>("id");
		c.user_access = users.get<int>("access");
	}
}

std::string helpers::auth::make_session(std::string username) {
	time_t rawtime;
	struct tm * timeinfo;
	int id;
	char buf[1024];
	db::result users = db::sql() << "select id from users where name = ?;" << username;
	
	if (!users.next()) {
		return "";
	}
	id = users.get<int>("id");
	users.clear();
	time(&rawtime);
	timeinfo  = localtime(&rawtime);
	strftime(buf,1024,"%c",timeinfo);
	std::string hash = helpers::hash::sha1hash_buf(buf);
	db::sql() << "insert into sessions values (?,?,'now');" << hash << id << cppdb::exec;
	return hash;
}

bool helpers::auth::session_exist(std::string session) {
	db::result sessions = db::sql() << "select count(*) from sessions left join users on users.id = userid where hash = ?" << session;
	sessions.next();
	return sessions.get<int>(0) == 1;
}

bool helpers::auth::user_exist(std::string username, std::string password_hash, bool raw) {
	if (raw) {
		password_hash = helpers::hash::sha1hash_buf(password_hash.c_str());
	}
	db::result users = db::sql() << "select count(*) from users where name = ? and password_hash = ?" << username << password_hash;
	users.next();
	return users.get<int>(0) == 1;
}

