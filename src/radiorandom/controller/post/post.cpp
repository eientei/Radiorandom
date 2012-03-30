#include "post.hpp"

post::post(cppcms::service & srv) : generic_controller(srv,"Post") {
	dispatcher().assign("/*",&post::index,this);
	mapper().assign("");
}


void post::index() {
	content::post c;
	render("html","post",c);
}
