#include "installer.hpp"

installer::installer(cppcms::service & srv) : generic_controller(srv,"Installer") {
	dispatcher().assign("/*",&installer::index,this);
	mapper().assign("");

	dispatcher().assign("/install/*",&installer::install,this);
	mapper().assign("install","/install");
}

void installer::index() {
	content::installer c;
	render("html","installer",c);
}

void installer::install() {
	std::string m_lock = settings().find("cms.install_lock_file").get_value<std::string>();
	util::fs::create_file(m_lock);

	content::installer_install c;
	render("html","installer_install",c);

	/*
	response().out() << "Done<br/>";
	response().out() << "Shutting down everything<br/>";
	response().out() << "<a href=\"" << url("/") << "\">index</a><br/>";
	*/
	service().shutdown();
}
