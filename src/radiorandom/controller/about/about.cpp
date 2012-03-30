#include "about.hpp"

about::about(cppcms::service & srv) : generic_controller(srv,"About") {
	dispatcher().assign("/*",&about::index,this);
	mapper().assign("");
}


void about::index() {
	content::about c;
	render("html","about",c);
}
