#include "controller.hpp"

controller::server::server(cppcms::service &srv, const std::string &name)
    : generic(srv,name)
{

}

controller::server::~server() {

}

void controller::server::serve_small(const std::string &path, std::string const& type) {
    std::ifstream f(path.c_str());
    if (f == NULL) {
        error(404);
        f.close();
        return;
    }
    response().content_type(type);
    response().out() << f.rdbuf();
    f.close();
}

void controller::server::serve_big(const std::string &path) {
    std::ifstream f(path.c_str());
    if (f == NULL) {
        error(404);
        f.close();
        return;
    }
    // stub
}
