#ifndef CONTROLLER_POST_HPP
#define CONTROLLER_POST_HPP

#include <radiorandom/controller/generic_controller.hpp>

class post : public generic_controller {
	public:
		post(cppcms::service & srv);
	public:
		void index();
};


#endif
