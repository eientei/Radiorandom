#include "installer.hpp"

installer::installer(cppcms::service & srv) : generic_controller(srv,"Installer") {
	dispatcher().assign("/*",&installer::index,this);
	mapper().assign("");

	dispatcher().assign("/install/*",&installer::install,this);
	mapper().assign("install","/install");
}

void installer::index() {
	content::installer::index c;
	display(c,"installer_index");
}

void installer::install() {
	std::string m_lock = settings().find("cms.install_lock_file").get_value<std::string>();
	util::fs::create_file(m_lock);

	content::installer::install c;
	display(c,"installer_install");
	
	service().shutdown();
}
