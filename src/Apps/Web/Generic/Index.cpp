#include "../Web.h"

void Web::Index(std::string skin) {
	if (skin.empty()) skin = default_skin;
	Generic::DB::Posts posts;
	Models::Generic::Index c;
	Prepare(c,"[Index]");
	c.index_files = posts.PostsCount();
	c.index_files_size = posts.PostsSize();
	render(skin,"Index",c);
}

