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

#include <cppdb/frontend.h>

#include <iostream>
#include <stdlib.h>
#include <magic.h>
#include <fcntl.h>

#include <Helpers/Helpers.h>
#include <Models/Models.h>
#include <Data/PString/PString.h>

using namespace std;

/// Radiorandom controller
class controller : public cppcms::application {
	private:
		/// Prepares model to rendering
		void prepare(model::master &c, menu_item current, bool login = false);
		/// Returns get reqest alue
		///
		/// \param [in] option to get
		/// @return option value
		string get_get(string option);
	public:
		/// Controller constructor
		controller(cppcms::service &srv);
	public:
		/// Main [dispatching] function
		///
		/// \param [in] url to dispatch
		virtual void main(string url);
	public:
		/// Terms of Service controller
		void tos();
		/// Setup site controller
		void setup();
		/// Index page controller
		void index();
	public:
		/// Users list controller
		void users();
		/// New user controller
		void users_new();
		/// Show user controller
		void users_show(string id);
		/// User login controller
		void users_login();
		/// User logout controller
		void users_logout();
		/// User profile controller
		void users_profile();
		/// User change password controller
		void users_profile_password();
		/// User change email controller
		void users_profile_email();
		/// User settings controller
		void users_profile_settings();
	public:
		/// Posts list controller
		void posts();
		/// New post controller
		void posts_new();
		/// Post show by id controller
		void posts_show_id(string id);
		/// Post show by hash controller
		void posts_show_hash(string hash);
		/// Post show by tags controller
		void posts_show_tags(string tags);
		/// Post show by date controller
		void posts_show_date(string date);
		/// Voteup posts controller
		void posts_voteup(string id);
		/// Votedown posts controller
		void posts_votedown(string id);
};

#endif
