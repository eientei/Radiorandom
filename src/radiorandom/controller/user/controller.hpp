#ifndef CONTROLLER_USER_HPP
#define CONTROLLER_USER_HPP

#include <radiorandom/controller/generic/controller.hpp>

#include <radiorandom/model/user/index.hpp>

namespace controller {
    class user : public generic {
        public:
            user(cppcms::service & srv);
        public:
            virtual void index();
    };
}

#endif // CONTROLLER_USER_HPP
