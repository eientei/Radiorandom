#include "../Web.h"

void Web::Setup(std::string skin) {
	if (skin.empty()) skin = default_skin;
	Models::Generic::Setup c;
	Prepare(c,"[Setup]");
	std::string lock = GetFromConfig<std::string>("setup.lockfile");
	if (Generic::FileSystem::Check(lock).ExistFile()) {
		render(skin,"Setup",c);
		return;
	}
	if(request().request_method()=="POST") {
		c.load(context());
		c.clear();
		Generic::FileSystem::Create(lock).CreateFile();
		std::string schema = GetFromConfig<std::string>("setup.db-schema");
		
		Static::DB::Interact.LoadSchema(schema);
		response().set_redirect_header("/");
	}
	render(skin,"Setup",c);
}


