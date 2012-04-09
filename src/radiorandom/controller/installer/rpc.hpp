#ifndef CONTROLLER_RPC_INSTALLER_HPP
#define CONTROLLER_RPC_INSTALLER_HPP

#include <radiorandom/controller/generic/rpc.hpp>

#include <radiorandom/util/string/util.hpp>

namespace controller {
    class installer_rpc : public generic_rpc {
        public:
            installer_rpc(cppcms::service & srv);
            void install_progress();

            static void reset();
            static void set_state(bool state);
            static void set_current(int count);
            static void set_total(int count);
        private:
            static bool m_is_installing;
            static int m_current;
            static int m_total;
    };
}


#endif // CONTROLLER_RPC_INSTALLER_HPP
