#ifndef MANAGER_SQL_HPP
#define MANAGER_SQL_HPP

#include <map>

namespace manager { class sql; }

#include <radiorandom/controller/generic/superclass.hpp>

#include <radiorandom/wrapper/session/wrapper.hpp>

namespace manager {
    class sql {
        public:
            wrapper::session & acquire(std::string const& name, bool is_static = false);
        private:
            typedef std::map<std::string,wrapper::session> session_map;
            session_map m_session_map;
    };
}

#endif // MANAGER_SQL_HPP
