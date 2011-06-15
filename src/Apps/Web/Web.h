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

//#include <Data/Data.h>
//#include <Proto/Proto.h>
#include <Models/Models.h>
#include <Generic/Generic.h>

/// Shortname for convinience
/*
typedef Data::Content::ItemMenu ItemMenu;

/// Main Web classs
class Web : public cppcms::application {
	private:
		/// Prepatre model for rendering, by filling with generic data.
		void Prepare(Models::Master::Master &c, ItemMenu current, ItemMenu submenu_current = ItemMenu(), bool login = false);
		
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
		void main(std::string url);
	public:
	
		/// Terms Of Service controiller
		void TOS(std::string skin);
		
		/// Setup controller
		void Setup(std::string skin);
		
		/// Index controller
		void Index(std::string skin);
		
	public:
		/// Users controller
		void Users(std::string skin);
};

*/
#endif

