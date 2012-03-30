#ifndef CONTROLLER_USER_HPP
#define CONTROLLER_USER_HPP

#include <radiorandom/controller/generic_controller.hpp>

class user : public generic_controller {
	public:
		user(cppcms::service & srv);
	public:
		void index();
};


#endif
