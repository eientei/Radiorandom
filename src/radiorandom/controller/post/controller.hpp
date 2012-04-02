#ifndef CONTROLLER_POST_HPP
#define CONTROLLER_POST_HPP

#include <radiorandom/controller/generic/controller.hpp>

#include <radiorandom/model/post/index.hpp>

namespace controller {
    class post : public generic {
        public:
            post(cppcms::service & srv);
        public:
            virtual void index();
    };
}


#endif // CONTROLLER_POST_HPP
