#include "controller.hpp"

controller::js::js(cppcms::service &srv)
    : server(srv,"js-server")
{
    dispatcher().assign("/*",&js::index,this);
    mapper().assign("");

    dispatcher().assign("/([a-zA-Z0-9_]*\\.js)",&js::serve_javascript,this,1);
    mapper().assign("js","/js{1}");
}


void controller::js::index() {
    content::js::index c;
    prepare(c,"js server");
    display(c,"js_index");
}

void controller::js::serve_javascript(std::string name) {
    serve_small(config().get<std::string>("cms.js_directory") + "/" + name,"text/javascript");
}
