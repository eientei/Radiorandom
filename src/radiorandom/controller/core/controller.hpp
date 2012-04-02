#ifndef CONTROLLER_CORE_HPP
#define CONTROLLER_CORE_HPP

#include <radiorandom/controller/generic/controller.hpp>

#include <radiorandom/model/core/index.hpp>

namespace controller {
    class core;
}

#include <radiorandom/controller/installer/controller.hpp>
#include <radiorandom/controller/user/controller.hpp>
#include <radiorandom/controller/post/controller.hpp>

namespace controller {
    class core : public generic {
        public:
            core(cppcms::service & srv);
        public:
            virtual void index();
    };
}

#endif // CONTROLLER_CORE_HPP
