#ifndef CONTROLLER_CORE_HPP
#define CONTROLLER_CORE_HPP

#include <radiorandom/controller/generic_controller.hpp>

class core;

#include "post/post.hpp"
#include "user/user.hpp"
#include "installer/installer.hpp"
#include "about/about.hpp"

class core : public generic_controller {
	public:
		core(cppcms::service & srv);
	public:
		void index();
//		void please_install();
//	public:
//		bool is_installed();
};


#endif
