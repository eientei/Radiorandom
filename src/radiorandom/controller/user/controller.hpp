#ifndef CONTROLLER_USER_HPP
#define CONTROLLER_USER_HPP

#include <radiorandom/controller/generic/controller.hpp>

#include <radiorandom/model/user/index.hpp>
#include <radiorandom/model/user/list.hpp>
#include <radiorandom/model/user/signup.hpp>

namespace controller {
    class user : public generic {
        public:
            user(cppcms::service & srv);
        public:
            virtual void index();
            virtual void list();
            virtual void signup();
        protected:
            virtual void prepare(content::generic &c, std::string submenu_item);
    };
}

#endif // CONTROLLER_USER_HPP
