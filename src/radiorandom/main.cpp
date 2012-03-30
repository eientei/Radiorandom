#include <iostream>

#include <signal.h>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>

#include "controller/core/core.hpp"

bool should_run = true;
cppcms::service * service;

void sighandler(int sig) {
	std::cout << "Shutting down by interruption from terminal" << std::endl;
	should_run = false;
	service->shutdown();
}

int main(int argc, char ** argv) {
	std::cout << "Initialized" << std::endl;
	signal(SIGINT, &sighandler);

	try {
		while (should_run) {
			service = new cppcms::service(argc,argv);
			service->applications_pool().mount(cppcms::applications_factory<core>());
			service->run();
			delete service;
		}
	} catch (std::exception const& e) {
		std::cout << e.what() << std::endl;
	}
	return 0; 
}
