#include "generic_controller.hpp"

void generic_controller::init_error_codes() {
	m_error_codes[404] = "Not Found";
	m_error_codes[403] = "Access Denied";
}
