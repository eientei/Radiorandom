#ifndef SERVER_H
#define SERVER_H

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_cookie.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/applications_pool.h>
#include <cppcms/json.h>

#include <radiorandom.h>

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class radio_random : public cppcms::application {
	private:
		bool valid_user_cookie();
		void set_menu(radiorandom::menu &c, menu_item current = menu_item("None","None"), bool login = false);
	public:
		radio_random(cppcms::service &srv);
		void users();
		void users_new();
		void users_show(std::string id);
		void users_login();
		void users_logout();
		void tos();
		void setup();
		void index();
		virtual void main(std::string url);		
};

#endif
