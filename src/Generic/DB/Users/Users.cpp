#include "Users.h"

int Generic::DB::Users::UsersCount(std::string where) {
	Static::DB::Interact.Lock();
	Generic::DB::Interact::Result users = Static::DB::Interact << "select count(*) from users " + where;
	Static::DB::Interact.Unlock();
	users.next();
	return users.get<int>(0);
}

Generic::DB::Interact::Result Generic::DB::Users::FetchUsersList(int limit, int offset,std::string sortby, std::string order, std::string where) {
	Static::DB::Interact.Lock();
	Generic::DB::Interact::Result users = Static::DB::Interact << "select id,access,name,password_hash,email,unixtime(joined) as joined,score,changer,unixtime(changed) as changed from users where id in (select id from users " + where + " order by " + sortby + " " + order + " limit ? offset ?) order by " + sortby + " " + order  << limit << offset;
	Static::DB::Interact.Unlock();
	return users;
}

/*
Generic::DB::Interact::Result Generic::DB::Users::FetchUsersList(int limit, int offset,std::string sortby, std::string order) {
	Static::DB::Interact.Lock();
	Generic::DB::Interact::Result users = Static::DB::Interact << "select id from users order by " + sortby + " " + order + " limit ? offset ?" << limit << offset;
	Static::DB::Interact.Unlock();
	return users;
}
*/
void Generic::DB::Users::AuthUser(Models::Master::Generic &c, std::string session) {
	c.user.authed = false;
	if (ExistSession(session)) {
		Static::DB::Interact.Lock();
		Generic::DB::Interact::Result users = Static::DB::Interact << "select id,access,name,password_hash,email,unixtime(joined) as joined,score,changer,unixtime(changed) as changed from sessions left join users on users.id = userid where hash = ?" << session;
		Static::DB::Interact.Unlock();
		users.next();
		FillItemUser(c.user,users);
		c.user.authed = true;
	}
}


std::string Generic::DB::Users::MakeSession(std::string username) {
	time_t rawtime;
	struct tm *timeinfo;
	char salt[1024];
	Static::DB::Interact.Lock();
	Generic::DB::Interact::Result users = Static::DB::Interact << "select id from users where name = ?" << username;
	Static::DB::Interact.Unlock();
	
	if(!users.next()) {
		return "";
	}
	int userid = users.get<int>("id");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(salt,1024,"%c",timeinfo);
	std::string hash = Generic::Hash::SHA1(salt).str();
	Static::DB::Interact.Lock();
	Static::DB::Interact << "insert into sessions values (?,?,'now')" << hash << userid << Generic::DB::Interact::Exec;
	Static::DB::Interact.Unlock();
	return hash;
}

void Generic::DB::Users::DeleteSession(std::string hash) {
	Static::DB::Interact.Lock();
	Static::DB::Interact << "delete from sessions where hash = ?" << hash << Generic::DB::Interact::Exec;
	Static::DB::Interact.Unlock();
}

bool Generic::DB::Users::ExistSession(std::string session) {
	Static::DB::Interact.Lock();
	Generic::DB::Interact::Result sessions = Static::DB::Interact << "select count(*) from sessions where hash = ?" << session;
	Static::DB::Interact.Unlock();
	sessions.next();
	return (sessions.get<int>(0) == 1);
}
bool Generic::DB::Users::ExistUserName(std::string username) {
	Static::DB::Interact.Lock();
	Generic::DB::Interact::Result usernames = Static::DB::Interact << "select count(*) from users where name = ?" << username;
	Static::DB::Interact.Unlock();
	usernames.next();
	return (usernames.get<int>(0) == 1);
}

bool Generic::DB::Users::ExistUser(std::string username, std::string password, bool raw_password) {
	if (raw_password)
		password = Generic::Hash::SHA1(password).str();
	Static::DB::Interact.Lock();
	Generic::DB::Interact::Result users = Static::DB::Interact << "select count(*) from users where name = ? and password_hash = ?" << username << password;
	Static::DB::Interact.Unlock();
	users.next();
	return (users.get<int>(0) == 1);
}

void Generic::DB::Users::FillSetUsers(Generic::Data::Content::SetUsers &s, Generic::DB::Interact::Result &r) {

	while (r.next()) {
		Generic::Data::Content::SetUsers::ItemUser i;
		FillItemUser(i,r);
		s.AddItem(i);
	}
}

void Generic::DB::Users::FillSingleUser(Generic::Data::Content::SetUsers::ItemUser &c, int iid) {
	Static::DB::Interact.Lock();
	Generic::DB::Interact::Result user = Static::DB::Interact << "select id,access,name,password_hash,email,unixtime(joined) as joined,score,changer,unixtime(changed) as changed from users where id = ?" << iid;
	Static::DB::Interact.Unlock();
	
	if (user.next()) {
		Generic::DB::Users().FillItemUser(c,user);
	}
}

void Generic::DB::Users::FillItemUser(Generic::Data::Content::SetUsers::ItemUser &i, Generic::DB::Interact::Result &r) {
	i.authed         = false;
	if (!r.is_null("id"))
	i.id             = r.get<int>("id");
	if (!r.is_null("access"))
	i.access         = r.get<std::string>("access");
	if (!r.is_null("name"))
	i.name           = r.get<std::string>("name");
	if (!r.is_null("password_hash"))
	i.password_hash  = r.get<std::string>("password_hash");
	if (!r.is_null("email"))
	i.email          = r.get<std::string>("email");
	if (!r.is_null("joined"))
	i.joined         = r.get<int>("joined");
	if (!r.is_null("score"))
	i.score          = r.get<int>("score");
	if (!r.is_null("changer"))
	i.changer        = r.get<int>("changer");
	if (!r.is_null("changed"))
	i.changed        = r.get<int>("changed");
	
}


void Generic::DB::Users::PopulateAccessLevel(std::map<int,std::string> &accesses) {
	if (accesses.size() == 0) {
		Static::DB::Interact.Lock();
		Generic::DB::Interact::Result a = Static::DB::Interact << "select * from access_levels";	
		Static::DB::Interact.Unlock();
		while(a.next()) {
			accesses[a.get<int>("value")] = a.get<std::string>("name");
		}
	}
}


void Generic::DB::Users::CreateUser(std::string username, std::string password, std::string email, bool anonymous) {
	std::string hash = Generic::Hash::SHA1(password).str();
	Static::DB::Interact.Lock();
	Static::DB::Interact << "insert into users values (DEFAULT,'Member',?,?,?,'now',10,1,'now')" << username << hash << email << Generic::DB::Interact::Exec;
	Static::DB::Interact.Unlock();
}


void Generic::DB::Users::ChangeEmail(int id, int changer_id, std::string new_email) {
	Static::DB::Interact.Lock();
	Static::DB::Interact << "update users set email = ?, changer = ? where id = ?" << new_email << changer_id << id << Generic::DB::Interact::Exec;
	Static::DB::Interact.Unlock();
}
void Generic::DB::Users::ChangePassword(int id, int changer_id, std::string new_password) {
	std::string hash = Generic::Hash::SHA1(new_password).str();
	Static::DB::Interact.Lock();
	Static::DB::Interact << "update users set password_hash = ?, changer = ? where id = ?" << hash << changer_id << id << Generic::DB::Interact::Exec;
	Static::DB::Interact.Unlock();
}
