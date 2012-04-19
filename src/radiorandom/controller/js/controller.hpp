#ifndef CONTROLLER_JS_SERVER_HPP
#define CONTROLLER_JS_SERVER_HPP

#include <radiorandom/controller/generic/server.hpp>

#include <radiorandom/model/js/index.hpp>

namespace controller {
    class js : public generic_server {
        public:
            js(cppcms::service & srv);
            virtual void index();
            void serve_javascript(std::string script_name);
    };
}

#endif // CONTROLLER_JS_SERVER_HPP
