#include "rpc.hpp"

controller::generic_rpc::generic_rpc(cppcms::service &srv, std::string const& controller_name, std::string const& service_name)
    : superclass(service_name,controller_name), json_rpc_server(srv)
{

}

controller::generic_rpc::~generic_rpc() {

}
