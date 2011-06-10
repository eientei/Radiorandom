#include <Helpers/Auth/ValidUser.h>

bool valid_user(string username, string password_hash, bool raw) {
	if (raw) {
		password_hash = sha1hash_buf(password_hash.c_str());
	}
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result users = radiorandom_sql << "select count(*) from users where username = ? and password_hash = ?" << username << password_hash;
	users.next();
	return users.get<int>(0) == 1;
}

