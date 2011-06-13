#ifndef RADIORANDOM_APPS_SERVER
#define RADIORANDOM_APPS_SERVER

/// @file

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_cookie.h>
#include <cppcms/http_file.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/applications_pool.h>
#include <cppcms/json.h>
#include <uriparser/Uri.h>

#include <iostream>
#include <stdlib.h>
#include <magic.h>
#include <fcntl.h>

#include <radiorandom/plainio/plainio.h>

#include <radiorandom/db/db.h>
#include <radiorandom/models/models.h>
#include <radiorandom/data/data.h>
#include <radiorandom/helpers/helpers.h>



class controller : public cppcms::application {
	private:
		void prepare(models::master::master &c, data::content::menu_item current, bool login = false, data::content::menu_item submenu_current = data::content::menu_item());
		void make_error(int errorcode);
		std::string get_get(std::string option);
	public:
		controller(cppcms::service &srv);
	public:
		virtual void main(std::string url);
	public:
		void tos();
		void setup();
		void index();
	public:
		void users();
		void users_new();
		void users_search(std::string query);
		void users_show(std::string id);
		void users_login();
		void users_logout();
		void users_profile();
		void users_profile_password();
		void users_profile_email();
		void users_profile_settings();
	public:
		
		void posts();
		void posts_new();
		void posts_show_id(std::string id);
		void posts_show_hash(std::string hash);
		void posts_show_tags(std::string tags);
		void posts_show_date(std::string date);
		void posts_voteup(std::string id);
		void posts_votedown(std::string id);
};



#endif
