#ifndef CONTROLLER_GENERIC_SERVER_HPP
#define CONTROLLER_GENERIC_SERVER_HPP

#include <fstream>

#include "controller.hpp"

namespace controller {
    class generic_server : public generic {
        public:
            generic_server(cppcms::service & srv, std::string const& controller_name);
            virtual ~generic_server();
        protected:
            void serve_small(std::string const& path, std::string const& mime_type);
    };
}

#endif // CONTROLLER_GENERIC_SERVER_HPP
