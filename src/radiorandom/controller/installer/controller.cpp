#include "controller.hpp"

controller::installer::installer(cppcms::service &srv) : generic(srv,"installer") {
    dispatcher().assign("/*",&controller::installer::index,this);
    mapper().assign("");

    dispatcher().assign("/install/*",&controller::installer::install,this);
    mapper().assign("install","/install");

}

void controller::installer::index() {
    content::installer::index c;
    prepare(c,"index");
    display(c,"installer_index");
}

void controller::installer::install() {
    util::fs::create_file(lock_file());

    content::installer::install c;
    prepare(c,"install");
    display(c,"installer_install");

    service().shutdown();
}
