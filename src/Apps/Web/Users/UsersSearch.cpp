#include "../Web.h"

void Web::UsersSearch(std::string skin, std::string what) {
	if (skin.empty()) skin = default_skin;
	//printf("%s <<>> %s\n",skin.c_str(),what.c_str());
	//Models::Users::UsersSearch c;
	//Prepare(c,"[Users]","[Search]");
	std::map<std::string,std::string> fields;

	fields["id"]     = "numeric";
	fields["access"] = "string";
	fields["name"]   = "string";
	fields["joined"] = "date";
	fields["score"]  = "numeric";
	
	std::string sortby = GetFromGet<std::string>("sortby");
	std::string order = GetFromGet<std::string>("order");
	std::string page = GetFromGet<std::string>("page");
	std::string limit = GetFromGet<std::string>("limit");

	std::string str;
	size_t pos;
	
	str = "sortby="+sortby;
	pos = what.find(str);
	if (pos != std::string::npos && !sortby.empty()) {
		what.erase(pos-1,str.length()+1);
	}
	
	str = "order="+order;
	pos = what.find(str);
	if (pos != std::string::npos && !order.empty()) {
		what.erase(pos-1,str.length()+1);
	}
	
	str = "page="+page;
	pos = what.find(str);
	if (pos != std::string::npos && !page.empty()) {
		what.erase(pos-1,str.length()+1);
	}
	
	str = "limit="+limit;
	pos = what.find(str);
	if (pos != std::string::npos && !limit.empty()) {
		what.erase(pos-1,str.length()+1);
	}
	
	printf("%s\n",what.c_str());
	
	std::string where = Generic::DB::TagParser(what,fields,false).sql_where();
	if (!where.empty()) where = "where " + where;
	Users(skin,where);
	
	
//	std::map<std::string,std::map> enums;
	
	//enums["access"]
	
	
	
//	printf("%s < > %s\n",what.c_str(),skin.c_str());
//	render(skin,"UsersSearch",c);
}


