#ifndef CONTROLLER_ABOUT_HPP
#define CONTROLLER_ABOUT_HPP

#include <radiorandom/controller/generic_controller.hpp>

class about : public generic_controller {
	public:
		about(cppcms::service & srv);
	public:
		void index();
};


#endif
