#include "post.hpp"

post::post(cppcms::service & srv) : generic_controller(srv,"Post") {
	dispatcher().assign("/*",&post::index,this);
	mapper().assign("");

	dispatcher().assign("/upload/*",&post::upload,this);
	mapper().assign("upload","/upload");
}


void post::index() {
	content::post::index c;
	display(c,"post_index");
}

void post::upload() {
	content::post::upload c;
	display(c,"post_upload");
}
