#include "controller.hpp"

// public

controller::core::core(cppcms::service &srv)
    : generic(srv,"core")
{
    mapper().root("/");
    mapper().assign("");;
    mapper().assign("core","");

    attach(new controller::js(srv),"js","js{1}","/js((/.*)?)",1);
    attach(new controller::installer(srv),"installer","installer{1}","/installer((/.*)?)",1);
    if (!config().get<bool>("cms.is_installed")) {
        return;
    }
    dispatcher().assign("/*",&core::index,this);
    attach(new controller::user(srv),"user","user{1}","/user((/.*)?)",1);
}

void controller::core::index() {
    content::core::index c;
    prepare(c,"index");
    display(c,"core_index");
}
