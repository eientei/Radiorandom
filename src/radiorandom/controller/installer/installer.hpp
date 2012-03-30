#ifndef CONTROLLER_INSTALLER_HPP
#define CONTROLLER_INSTALLER_HPP

#include <radiorandom/controller/generic_controller.hpp>

class installer : public generic_controller {
	public:
		installer(cppcms::service & srv);
	public:
		void index();
		void install();
};


#endif
