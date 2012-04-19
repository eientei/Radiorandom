#ifndef CONTROLLER_SERVER_HPP
#define CONTROLLER_SERVER_HPP

#include <fstream>

#include <radiorandom/controller/generic/controller.hpp>

namespace controller {
    class server : public generic {
        public:
            server(cppcms::service & srv, std::string const& name);
            virtual ~server();
        protected:
            void serve_small(std::string const& path, std::string const& type);
            void serve_big(std::string const& path);
    };
}

#endif // CONTROLLER_SERVER_HPP
