#ifndef APPS_WEB_H
#define APPS_WEB_H

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

#include <map>

#include <Models/Models.h>
#include <Generic/Generic.h>
#include <Static/Static.h>
#include <Generic/FileSystem/Check/Check.h>
#include <Generic/FileSystem/Create/Create.h>
#include <Generic/Markup/Menu/Menu.h>
#include <Generic/DB/Users/Users.h>
#include <Generic/DB/Posts/Posts.h>
#include <Generic/DB/TagParser/TagParser.h>

/// Shortname for convinience

/// Main Web classs
class Web : public cppcms::application {
	private:
		/// Prepatre model for rendering, by filling with generic data.
		void Prepare(Models::Master::Master &c, std::string current, std::string submenu_current = "", bool login = false);
		
		/// Make and render an error with given code and message
		void MakeError(std::string skin="html", int error_code=404, std::string error_message="");
		
		/// Get a value from GET request
		template <typename T>
		T GetFromGet(std::string what);
		
		/// Get a value from COOKIE request
		std::string GetFromCookie(std::string what);
		
		/// Get a value from COOKIE request
		template <class T>
		T GetFromConfig(std::string what) {
			return settings().get<T>(what);
		}
		
		
		/// Default skin use to
		std::string default_skin;
		
	public:
		/// Constructor
		Web(cppcms::service &srv);
		
		/// Main dispatcher function
		///
		/// \param [in] url to dispatch
		void main(std::string url);
	public:
	
		/// Terms Of Service controiller
		///
		/// \param [in] skin to use
		void TOS(std::string skin);
		
		/// Setup controller
		///
		/// \param [in] skin to use
		void Setup(std::string skin);
		
		/// Index controller
		///
		/// \param [in] skin to use
		void Index(std::string skin);
		
	public:
		/// Users controller
		///
		/// \param [in] skin to use
		/// \param [in] where clause
		void Users(std::string skin, std::string where = "");
		
		/// Users Show controller
		///
		/// \param [in] id to show
		/// \param [in] skin to use
		void UsersShow(std::string id, std::string skin);
		
		/// Users register controller
		///
		/// \param [in] skin to use
		void UsersNew(std::string skin);
		
		/// Users logout controller
		///
		/// \param [in] skin to use
		void UsersLogout(std::string skin);
		
		/// Users login controller
		///
		/// \param [in] skin to use
		void UsersLogin(std::string skin);
		
		/// Users login controller
		///
		/// \param [in] skin to use
		void UsersProfile(std::string skin);
		
		/// Users password changing controller
		///
		/// \param [in] skin to use
		void UsersProfilePassword(std::string skin);
		
		/// Users email changing controller
		///
		/// \param [in] skin to use
		void UsersProfileEmail(std::string skin);
		
		/// Users settings changing controller
		///
		/// \param [in] skin to use
		void UsersProfileSettings(std::string skin);
		
		
		/// Users search controller
		///
		/// \param [in] skin to use
		/// \param [in] what to search
		void UsersSearch(std::string skin, std::string what);
};

#endif

