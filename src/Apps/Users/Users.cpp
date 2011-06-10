#include <Apps/Server.h>

void controller::users() {
	model::users c;
	prepare(c,menu_item("[Users]","/users"));
	string sortby = get_get("sortby");
	string order = get_get("order");
	string pagestr = get_get("page");
	string limitstr = get_get("limit");
	
	
	int softlimit = settings().get<int>("limits.users-soft");
	int hardlimit = settings().get<int>("limits.users-hard");
	if (limitstr.length() > 0) {
		sscanf(limitstr.c_str(),"%d",&softlimit);
	}
	if (softlimit > hardlimit) softlimit = hardlimit;
	if (softlimit < 0) softlimit = 0;
	int page = 1;
	sscanf(pagestr.c_str(),"%d",&page);
	if (page < 1) page = 1;
	
	if (   sortby != "score"
		&& sortby != "access"
		&& sortby != "username"
	) {
		sortby = "joined";
	}
	
	if (order != "asc") {
		order = "desc";
	}
	
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result users = radiorandom_sql << "select count(*) from users";
	users.next();
	int total_items = users.get<int>(0);
	char buf[1024];
	snprintf(buf,1024,"%d",softlimit);
	c.prefix = "?sortby=" + sortby + "&amp;order=" + order + "&amp;limit=" + buf;
	if (total_items > softlimit) {
		c.many_items = true;
		c.page = page;
		c.total_items = total_items;
		c.page_size = softlimit;
		snprintf(buf,1024,"%d",page);
		c.suffix = "&amp;page=" + string(buf);
	}
	users = radiorandom_sql << "select * from users order by " + sortby + " " + order + " limit ? offset ?" << softlimit << (page-1) * softlimit;
	while (users.next()) {
		string username = users.get<string>("username");
		int id = users.get<int>("id");
		int score = users.get<int>("score");
		int access = users.get<int>("access");
		int joined = users.get<int>("joined");
		c.usersset.push_back(user_item(username,score,access,joined,id));
	}
	
	if (sortby == "username") {
		if (order == "asc") c.sortdir_username = "desc";
		else c.sortdir_username = "asc";
	} else if (sortby == "score") {
		if (order == "asc") c.sortdir_score = "desc";
		else c.sortdir_score = "asc";
	} else if (sortby == "access") {
		if (order == "asc") c.sortdir_access = "desc";
		else c.sortdir_access = "asc";
	} else if (sortby == "joined") {
		if (order == "asc") c.sortdir_joined = "desc";
		else c.sortdir_joined = "asc";
	}
	render("html_users",c);	
}
