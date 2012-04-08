#ifndef CONTROLLER_GENERIC_RPC_HPP
#define CONTROLLER_GENERIC_RPC_HPP

#include <string>

#include <booster/function.h>

#include <cppcms/service.h>
#include <cppcms/json.h>
#include <cppcms/rpc_json.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

namespace controller {
    class generic_rpc : public  cppcms::rpc::json_rpc_server {
        public:
            generic_rpc(cppcms::service & srv, std::string const& rpc_name);
            virtual ~generic_rpc();
        protected:
            std::string m_rpc_name;
    };
}

#endif // CONTROLLER_GENERIC_RPC_HPP