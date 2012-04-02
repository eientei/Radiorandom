#ifndef CONTROLLER_INSTALLER_HPP
#define CONTROLLER_INSTALLER_HPP

#include <radiorandom/controller/generic/controller.hpp>

#include <radiorandom/model/installer/index.hpp>
#include <radiorandom/model/installer/install.hpp>

namespace controller {
    class installer : public generic {
        public:
            installer(cppcms::service & srv);
        public:
            virtual void index();
            virtual void install();
    };
}

#endif // CONTROLLER_INSTALLER_HPP
