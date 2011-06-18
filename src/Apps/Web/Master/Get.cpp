#include "../Web.h"

std::string Web::GetFromCookie(std::string what) {
	return request().cookie_by_name(what).value();
}

template <>
int Web::GetFromGet(std::string what) {
	cppcms::http::request::form_type gets = request().get();
	cppcms::http::request::form_type::const_iterator it = gets.find(what);	
	if (it == gets.end()) return -1;
	std::string value = it->second;
	if (value.empty()) return -1;
	return atoi(value.c_str());
}

template <>
std::string Web::GetFromGet(std::string what) {
	cppcms::http::request::form_type gets = request().get();
	cppcms::http::request::form_type::const_iterator it = gets.find(what);	
	if (it == gets.end()) return "";
	std::string value = it->second;
	if (value.empty()) return "";
	return value;
}
