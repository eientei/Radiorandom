#include "controller.hpp"


controller::installer::installer(cppcms::service &srv)
    : generic(srv,"installer")
{
    dispatcher().assign("/*",&controller::installer::index,this);
    mapper().assign("");

    dispatcher().assign("/install/*",&controller::installer::install,this);
    mapper().assign("install","/install");

    dispatcher().assign("/install_finished/*",&controller::installer::install_finished,this);
    mapper().assign("install_finished","/install_finished");
}

void controller::installer::index() {
    content::installer::index c;
    prepare(c,"index");
    display(c,"installer_index");
}

void controller::installer::install() {
    content::installer::install c;
    prepare(c,"install");
    display(c,"installer_install");
}

void controller::installer::install_finished() {
    lock("install_finished");
    update_installed_state();
    if (!is_installed()) {
        std::cout << "installing" << std::endl;
        std::ifstream schema_template_stream(schema_template().c_str());
        update(schema_template_stream);
        content::installer::install_finished c;
        prepare(c,"install_finished");
        display(c,"installer_install_finished");
    }
    unlock("install_finished");
}
