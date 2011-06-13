#include <radiorandom/apps/server.h>

/// @file

controller::controller(cppcms::service &srv) :
	cppcms::application(srv)
{
}

void controller::prepare(models::master::master &c, data::content::menu_item current, bool login, data::content::menu_item submenu_current) {
	if (helpers::filesystem::file_exists(settings().get<std::string>("setup.lockfile"))) {
		c.setted_up = true;
	}
	if (c.setted_up) {
		helpers::auth::auth_user(c,request().cookie_by_name("session").value());
	}
	helpers::navigation::gen_menu(c,current,login,submenu_current);
}

void controller::make_error(int error_code) {
		models::generic::error c;
		prepare(c,data::content::menu_item("[Error]","/"));
		c.error_code = error_code;
		render("html_error",c);
}


void controller::main(std::string url) {

	if (!helpers::filesystem::file_exists(settings().get<std::string>("setup.lockfile"))) {
		if (url != "/setup") {
			response().set_redirect_header("/setup");
			return;
		}
	}
	if (!dispatcher().dispatch(url)) {
		make_error(404);
	}
}

int main(int argc, char **argv) {
	try {		
		pio_init();
		db::connect();
		printf("Server fired us\n");
		cppcms::service srv(argc,argv);
		srv.applications_pool().mount(cppcms::applications_factory<controller>());
		srv.run();		
	} catch(std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
