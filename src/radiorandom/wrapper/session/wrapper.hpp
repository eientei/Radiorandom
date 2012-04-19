#ifndef WRAPPER_SESSION_HPP
#define WRAPPER_SESSION_HPP

#include <string>

#include <cppdb/frontend.h>

namespace wrapper {
    class session : public cppdb::session {
        public:
            session();
            session(std::string const& name, bool is_static);
            std::string const& name();
        private:
            std::string m_name;
    };
}

#endif // WRAPPER_SESSION_HPP
