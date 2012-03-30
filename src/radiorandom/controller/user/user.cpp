#include "user.hpp"

user::user(cppcms::service & srv) : generic_controller(srv,"User") {
	dispatcher().assign("/*",&user::index,this);
	mapper().assign("");
}


void user::index() {
	content::user::index c;
	display(c,"user_index");
}
