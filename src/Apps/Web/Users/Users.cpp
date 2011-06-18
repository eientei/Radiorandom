#include "../Web.h"

void Web::Users(std::string skin, std::string where) {

	if (skin.empty()) skin = default_skin;
	Models::Users::Users c;
	c.items.show_sort = true;
	Prepare(c,"[Users]");

	std::string sortby = GetFromGet<std::string>("sortby");
	std::string order = GetFromGet<std::string>("order");
	std::string search = GetFromGet<std::string>("search");
	int page = GetFromGet<int>("page");
	int limit = GetFromGet<int>("limit");
	
	c.search.value(search);
	
	if(request().request_method()=="POST") {
		c.load(context());
		/*
		c.what = "/users/" + c.search.value();
		*/
	}
	
	if (!c.search.value().empty()) {
		std::map<std::string,std::string> fields;
		fields["id"]     = "numeric";
		fields["access"] = "string";
		fields["name"]   = "string";
		fields["joined"] = "date";
		fields["score"]  = "numeric";
		std::string c_where = Generic::DB::TagParser(c.search.value(),fields,false).sql_where();
		if (!c_where.empty()) where = "where " + c_where;
	}
	
	int softlimit = GetFromConfig<int>("limits.users-soft");
	int hardlimit = GetFromConfig<int>("limits.users-hard");
	if (limit < 1) limit = softlimit;
	if (limit > hardlimit) limit = hardlimit;
	if (page < 1) page = 1;
	
	if (
		sortby != "name" &&
		sortby != "access" &&
		sortby != "score"
	) {
		sortby = "joined";
	}
	
	if (order != "asc") {
		order = "desc";
	}

	Generic::Data::Format formatter;
	
	std::string what;
	
	if (!c.search.value().empty()) what = "&search=" + c.search.value();
	
	Generic::Data::Content::ContentURL url(
		"?sortby=" + sortby + "&amp;order=" + order,
		"&amp;limit=" + formatter.ToString(limit) + what,
		"&amp;page=" + formatter.ToString(page)
	);
	
	int total = Generic::DB::Users().UsersCount(where);
	c.items = Generic::Data::Content::SetUsers(total,page,limit,url);
	Generic::DB::Interact::Result users = Generic::DB::Users().FetchUsersList(limit,(page-1) * limit,sortby,order,where);
	Generic::DB::Users().FillSetUsers(c.items,users);
	/*
	 	Generic::DB::Interact::Result users = Generic::DB::Users().FetchUsersList(limit,(page-1) * limit,sortby,order);
	while (users.next()) {
		int id = users.get<int>(0);
		Generic::Data::Content::SetUsers::ItemUser z;
		Generic::DB::Users().FillSingleUser(zy,id);
	}
	 */
	
	if (sortby == "name") {
		if (order == "asc") c.sort_directions_username = "desc";
		else c.sort_directions_username = "asc";
	} else if (sortby == "score") {
		if (order == "asc") c.sort_directions_score = "desc";
		else c.sort_directions_score = "asc";
	} else if (sortby == "access") {
		if (order == "asc") c.sort_directions_access = "desc";
		else c.sort_directions_access = "asc";
	} else if (sortby == "joined") {
		if (order == "asc") c.sort_directions_joined = "desc";
		else c.sort_directions_joined = "asc";
	}
	
	render(skin,"Users",c);
}
