#ifndef CONTROLLER_GENERIC_RPC_HPP
#define CONTROLLER_GENERIC_RPC_HPP

#include <string>

#include <cppcms/service.h>
#include <cppcms/json.h>
#include <cppcms/rpc_json.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include "superclass.hpp"

namespace controller {
    class generic_rpc : public superclass, public cppcms::rpc::json_rpc_server {
        public:
            generic_rpc(cppcms::service & srv, std::string const& controller_name, std::string const& service_name = "RPC");
            virtual ~generic_rpc();
    };
}

#endif // CONTROLLER_GENERIC_RPC_HPP
