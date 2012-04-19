#ifndef CONTROLLER_INSTALLER_HPP
#define CONTROLLER_INSTALLER_HPP

#include <fstream>

#include <radiorandom/controller/generic/controller.hpp>

#include <radiorandom/model/installer/index.hpp>
#include <radiorandom/model/installer/install.hpp>
#include <radiorandom/model/installer/install_finished.hpp>

#include <radiorandom/util/sql/util.hpp>

#include "rpc.hpp"

namespace controller {
    class installer : public generic {
        public:
            installer(cppcms::service & srv);
            virtual void index();
            virtual void install();
            virtual void install_finished(std::string url);
    };
}

#endif // CONTROLLER_INSTALLER_HPP
