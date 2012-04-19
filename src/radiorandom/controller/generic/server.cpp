#include "server.hpp"

controller::generic_server::generic_server(cppcms::service &srv, std::string const& controller_name)
    : generic(srv,controller_name,"SRV")
{

}

controller::generic_server::~generic_server() {

}

void controller::generic_server::serve_small(std::string const& path, std::string const& mime_type) {
    std::ifstream f(path.c_str());
    if (f == NULL) {
        error(404);
        f.close();
        return;
    }
    response().content_type(mime_type);
    response().out() << f.rdbuf();
    f.close();
}
