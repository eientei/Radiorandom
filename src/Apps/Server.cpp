#include <Apps/Server.h>

/// @file

string controller::get_get(string option) {
	if (request().get().find(option) != request().get().end())
		return request().get().find(option)->second;
	return "";
}

void controller::prepare(model::master &c, menu_item current, bool login) {
	if (file_exists(settings().get<std::string>("setup.lockfile"))) {
		c.setted_up = true;
	}
	if (c.setted_up) {
		auth_user(c,request().cookie_by_name("session").value());
	}
	gen_menu(c,current,login);
}

controller::controller(cppcms::service &srv) :
	cppcms::application(srv)
{
	dispatcher().assign("/",&controller::index,this);
	dispatcher().assign("/setup($|/$)",&controller::setup,this);
	dispatcher().assign("/tos($|/$)",&controller::tos,this);
	
	dispatcher().assign("/users($|/$|\\?.*)",&controller::users,this);
	dispatcher().assign("/users/([0-9]*)",&controller::users_show,this,1);
	dispatcher().assign("/users/new",&controller::users_new,this);
	dispatcher().assign("/users/logout",&controller::users_logout,this);
	dispatcher().assign("/users/login",&controller::users_login,this);
	dispatcher().assign("/users/profile",&controller::users_profile,this);
	dispatcher().assign("/users/profile/password",&controller::users_profile_password,this);
	dispatcher().assign("/users/profile/email",&controller::users_profile_email,this);
	dispatcher().assign("/users/profile/settings",&controller::users_profile_settings,this);
	
	dispatcher().assign("/posts($|/$|\\?.*)",&controller::posts,this);
	dispatcher().assign("/posts/new",&controller::posts_new,this);
	dispatcher().assign("/possts/id/([0-9]*)",&controller::posts_show_id,this,1);
	dispatcher().assign("/possts/hash/([0-9a-fA-F]{32})",&controller::posts_show_hash,this,1);
	dispatcher().assign("/possts/tags/(.*)",&controller::posts_show_tags,this,1);
	dispatcher().assign("/possts/date/(.*)",&controller::posts_show_date,this,1);
	dispatcher().assign("/possts/voteup/([0-9]*)",&controller::posts_voteup,this,1);
	dispatcher().assign("/possts/votedown/([0-9]*)",&controller::posts_votedown,this,1);
}

void controller::main(string url) {
	if (!file_exists(settings().get<std::string>("setup.lockfile"))) {
		if (url != "/setup") {
			response().set_redirect_header("/setup");
			return;
		}
	}
	if (!dispatcher().dispatch(url)) {
		model::error c;
		prepare(c,menu_item("[Error]","/"));
		c.errorcode = 404;
		render("html_error",c);
	}
}

/// Main function
///
/// \param [in] argc arguments count
/// \param [in] argv arguments list
/// @return zero
int main(int argc, char **argv) {
	printf("Server fired up\n");
	pio_init();
	try {
		cppcms::service srv(argc,argv);
		srv.applications_pool().mount(cppcms::applications_factory<controller>());
		srv.run();
	} catch(std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
