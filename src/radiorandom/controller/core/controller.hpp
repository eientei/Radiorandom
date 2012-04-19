#ifndef CONTROLLER_CORE_HPP
#define CONTROLLER_CORE_HPP

#include <radiorandom/controller/generic/controller.hpp>
#include <radiorandom/model/core/index.hpp>

#include <radiorandom/controller/js/controller.hpp>
#include <radiorandom/controller/installer/controller.hpp>

namespace controller {
    class core : public generic {
        public:
            core(cppcms::service & srv);
            virtual void index();
    };
}

#endif // CONTROLLER_CORE_HPP
