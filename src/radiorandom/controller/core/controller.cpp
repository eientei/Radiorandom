#include "controller.hpp"

controller::core::core(cppcms::service &srv)
    : generic(srv,"core")
{
    mapper().root("/");
    mapper().assign("");
    mapper().assign("core","");

    attach(new controller::js(srv),"js","js{1}","/js((/.*)?)",1);
    attach(new controller::installer(srv),"installer","installer{1}","/installer((/.*)?)",1);
    if (!config().get<bool>("cms.is_installed")) {
        return;
    }

    dispatcher().assign("/*",&core::index,this);

}

void controller::core::index() {
    content::core::index c;
    display(c,"index","core_index");
}
