#ifndef WRAPPER_SQL_SESSION_HPP
#define WRAPPER_SQL_SESSION_HPP

#include <string>

#include <cppdb/frontend.h>
#include <cppdb/mutex.h>

namespace wrapper {
    namespace sql {
        class session : public cppdb::session {
            public:
                session(std::string const& name, bool is_static = false);
            private:
                std::string m_name;
                bool m_is_static;

        };
    }
}

#endif // WRAPPER_SQL_SESSION_HPP
