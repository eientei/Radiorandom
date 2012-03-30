#ifndef CONTROLLER_CORE_HPP
#define CONTROLLER_CORE_HPP

#include <radiorandom/controller/generic_controller.hpp>

class core;

#include <radiorandom/controller/post/post.hpp>
#include <radiorandom/controller/user/user.hpp>
#include <radiorandom/controller/installer/installer.hpp>

class core : public generic_controller {
	public:
		core(cppcms::service & srv);
	public:
		void index();
};


#endif
