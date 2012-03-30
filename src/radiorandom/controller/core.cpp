#include "core.hpp"

core::core(cppcms::service & srv) : generic_controller(srv,"Core") {
	mapper().root("/");
	
	if (!is_installed()) {	
		attach(new installer(srv), "installer", "installer{1}", "/installer((/.*)?)",1);
		mapper().assign("");
		return;
	}

	attach(new post(srv), "post", "post{1}", "/post((/.*)?)",1);
	attach(new user(srv), "user", "user{1}", "/user((/.*)?)",1);
	attach(new about(srv), "about", "about{1}", "/about((/.*)?)",1);

	dispatcher().assign("/*",&core::index,this);
	mapper().assign("");
}

void core::index() {
	content::core c;
	render("html","core",c);
}

