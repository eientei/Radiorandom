#ifndef GENERIC_CONTROLLER_HPP
#define GENERIC_CONTROLLER_HPP

#include <string>
#include <map>

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include <radiorandom/model/model.hpp>

#include <radiorandom/util/util.hpp>

class generic_controller : public cppcms::application {
	private:
		std::string m_controller_name;
		std::map<int,std::string> m_error_codes;	
		bool m_is_installed;
	public:
		generic_controller(cppcms::service & srv, std::string name);
		virtual ~generic_controller() = 0;
	public:
		std::string const& get_controller_name();
		bool is_installed();
	public:
		virtual void main(std::string url);
		virtual void index() = 0;
		virtual void please_install();
	protected:
		void error(int code, std::string message = "");
		void do_dispatch(std::string const& url);
	private:
		void init_error_codes();
};


#endif
