#include "Web.h"

/// @file

/// Main function of Web server
///
/// \param [in] argc arguments count
/// \param [in] argv arguments list
///
/// @return zero
int main(int argc, char **argv) {
	Generic::IO::PIO pio; // Inits IO
	printf("Server fired up\n");
	try {
		cppcms::service srv(argc,argv);
		srv.applications_pool().mount(cppcms::applications_factory<Web>());
		srv.run();		
	} catch (std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

