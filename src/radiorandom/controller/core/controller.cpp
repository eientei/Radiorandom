#include "controller.hpp"

// public

controller::core::core(cppcms::service &srv)
    : generic(srv,"core")
{
    mapper().root("/");
    mapper().assign("");
    mapper().assign("core","");

    if (!is_installed()) {
        attach(new controller::installer(srv),"installer","installer{1}","/installer((/.*)?)",1);
        return;
    }
    dispatcher().assign("/*",&core::index,this);
}

void controller::core::index() {
    content::core::index c;
    prepare(c,"index");
    display(c,"core_index");
}
