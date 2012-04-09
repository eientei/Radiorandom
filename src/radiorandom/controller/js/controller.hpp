#ifndef CONTROLLER_SERVER_JS_HPP
#define CONTROLLER_SERVER_JS_HPP

#include <radiorandom/controller/server/controller.hpp>

#include <radiorandom/model/js/index.hpp>

namespace controller {
    class js : public server {
        public:
            js(cppcms::service & srv);
            virtual void index();
            void serve_javascript(std::string name);
    };
}

#endif // CONTROLLER_SERVER_JS_HPP
