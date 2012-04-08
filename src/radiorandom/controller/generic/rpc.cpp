#include "rpc.hpp"

controller::generic_rpc::generic_rpc(cppcms::service &srv, std::string const& rpc_name)
    : json_rpc_server(srv), m_rpc_name(rpc_name)
{
    std::cout << "RPC [NEW]   " << m_rpc_name << std::endl;
}

controller::generic_rpc::~generic_rpc() {
    std::cout << "RPC [DEL]   " << m_rpc_name << std::endl;
}
