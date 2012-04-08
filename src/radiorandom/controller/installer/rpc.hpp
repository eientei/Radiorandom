#ifndef CONTROLLER_INSTALLER_RPC_HPP
#define CONTROLLER_INSTALLER_RPC_HPP

#include <radiorandom/util/string/util.hpp>

#include <radiorandom/controller/generic/rpc.hpp>

namespace controller {
    class installer_rpc : public generic_rpc {
        public:
            installer_rpc(cppcms::service & srv);
            void install_progress();

            void reset();
            void set_install_state(bool is_installing);
            void set_total_objects(int count);
            void set_current_objects(int count);
        private:
            bool m_is_installing;
            int m_total_objects;
            int m_current_objects;


    };
}

#endif // CONTROLLER_INSTALLER_RPC_HPP
