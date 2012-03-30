#include "generic_controller.hpp"

generic_controller::generic_controller(cppcms::service & srv, std::string name) : cppcms::application(srv), m_controller_name(name) { 
	
	std::string m_lock = settings().find("cms.install_lock_file").get_value<std::string>();
	m_is_installed = util::fs::file_exists(m_lock);


	init_error_codes();
	std::cout << "    [NEW]      " << m_controller_name << std::endl;
}

generic_controller::~generic_controller() { 
	std::cout << "    [DEL]      " << m_controller_name << std::endl;
}

void generic_controller::error(int code, std::string message) {
	if (message.empty()) message = m_error_codes[code];
	response().out() << code;
	if (!message.empty()) {
		response().out() << " - ";
		response().out() << message;
	}
}


void generic_controller::do_dispatch(std::string const& url) {
	if (!dispatcher().dispatch(url)) {
		if (is_installed()) {
			error(404);
		} else {
			please_install();
		}
	}
}

std::string const& generic_controller::get_controller_name() {
	return m_controller_name;
}


void generic_controller::main(std::string url) {
	do_dispatch(url);
}

bool generic_controller::is_installed() {
	return m_is_installed;
}
void generic_controller::please_install() {
	content::installer::please_install c;
	display(c,"installer_please_install");
}

void generic_controller::prepare(content::generic_model & c) {
	c.is_installed = m_is_installed;
}

void generic_controller::display(content::generic_model & c, std::string tmpl, std::string skin) {
	prepare(c);
	render(skin,tmpl,c);
}
