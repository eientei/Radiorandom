#include "Users.h"


void Generic::DB::Users::AuthUser(Models::Master::Generic &c, std::string session) {
	c.user.authed = false;
	if (ExistSession(session)) {
		Generic::DB::Interact::Result users = Generic::DB::Interact() << "select * from sessions left join users on users.id = userid where hash = ?" << session;
		users.next();
		FillItemUser(c.user,users);
		c.user.authed = true;
	}
}


std::string Generic::DB::Users::MakeSession(std::string username) {
	time_t rawtime;
	struct tm *timeinfo;
	char salt[1024];
	
	Generic::DB::Interact::Result users = Generic::DB::Interact() << "select count(*) from users where name = ?" << username;
	
	if(!users.next()) {
		return "";
	}
	int userid = users.get<int>("id");
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(salt,1024,"%c",timeinfo);
	std::string hash = Generic::Hash::SHA1(salt).str();
	Generic::DB::Interact() << "insert into sessions values (?,?,unixnow())" << hash << userid << Generic::DB::Interact::Exec;
	return hash;
}

bool Generic::DB::Users::ExistSession(std::string session) {
	Generic::DB::Interact::Result sessions = Generic::DB::Interact() << "select count(*) from sessions where hash = ?" << session;
	sessions.next();
	return (sessions.get<int>(0) == 1);
}

bool Generic::DB::Users::ExistUser(std::string username, std::string password, bool raw_password) {
	if (raw_password)
		password = Generic::Hash::SHA1(password).str();
	Generic::DB::Interact::Result users = Generic::DB::Interact() << "select count(*) from users where name = ? and password_hash = ?" << username << password;
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

void Generic::DB::Users::FillItemUser(Generic::Data::Content::SetUsers::ItemUser &i, Generic::DB::Interact::Result &r) {
	i.authed         = false;
	i.id             = r.get<int>("id");
	i.access         = r.get<int>("access");
	i.name           = r.get<std::string>("name");
	i.password_hash  = r.get<std::string>("password_hash");
	i.email          = r.get<std::string>("email");
	i.joined         = r.get<int>("joined");
	i.score          = r.get<int>("score");
	i.changer        = r.get<int>("changer");
	i.changed        = r.get<int>("changed");
	
}

