#include "controller.hpp"


controller::js::js(cppcms::service &srv)
    : generic(srv,"js server")
{
    dispatcher().assign("/*",&controller::js::index,this);
    mapper().assign("");

    dispatcher().assign("/([a-zA-Z0-9_]*\\.js)",&controller::js::serve_script,this,1);
    mapper().assign("js","/js{1}");
}

void controller::js::index() {
    content::js::index c;
    prepare(c,"js server");
    display(c,"js_index");
}

void controller::js::serve_script(std::string name) {
    std::ifstream f((js_directory() + "/" + name).c_str());
    if (f == NULL) {
        error(404);
        f.close();
        return;
    }
    response().content_type("text/javascript");
    response().out() << f.rdbuf();
    f.close();
}
