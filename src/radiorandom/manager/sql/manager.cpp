#include "manager.hpp"

wrapper::session & manager::sql::acquire(std::string const& name, bool is_static) {
    session_map::iterator it;
    it = m_session_map.find(name);
    if (it == m_session_map.end()) {
        wrapper::session session(name,is_static);
        session.open(controller::superclass::config().get<std::string>("sql.connection_string"));
        m_session_map.insert(std::make_pair<std::string,wrapper::session>(name,session));
        return m_session_map.at(name);
    } else {
        return it->second;
    }
}
