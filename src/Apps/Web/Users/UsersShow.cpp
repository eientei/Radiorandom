#include "../Web.h"

void Web::UsersShow(std::string id, std::string skin) {
	if (skin.empty()) skin = default_skin;
	Models::Users::UsersShow c;
	Prepare(c,"[Users]");
	printf("%s\n",id.c_str());
	int iid = atoi(id.c_str());
	Generic::DB::Users().FillSingleUser(c.item,iid);

	render(skin,"UsersShow",c);
}
