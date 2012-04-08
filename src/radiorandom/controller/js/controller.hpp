#ifndef CONTROLLER_JS_HPP
#define CONTROLLER_JS_HPP

#include <fstream>

#include <radiorandom/controller/generic/controller.hpp>

#include <radiorandom/model/js/index.hpp>

namespace controller {
    class js : public generic {
        public:
            js(cppcms::service & srv);
            virtual void index();
            void serve_script(std::string name);
    };
}

#endif // CONTROLLER_JS_HPP
