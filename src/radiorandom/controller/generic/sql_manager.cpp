#include "superclass.hpp"

cppdb::session & controller::sql_manager::session(std::string const& key) {
    std::map<std::string,cppdb::session>::iterator it;
    it = m_sessions.find(key);
    if (it == m_sessions.end()) {
        cppdb::session session;
        m_sessions[key] = session;
        return m_sessions[key];
    } else {
        return it->second;
    }
}

void controller::sql_manager::close(std::string const& key) {
    std::map<std::string,cppdb::session>::iterator it;
    it = m_sessions.find(key);
    if (it != m_sessions.end()) {
        it->second.close();
    }
}

void controller::sql_manager::close_all() {
    std::map<std::string,cppdb::session>::iterator it,end;
    end = m_sessions.end();
    for (it = m_sessions.begin(); it != end; ++it) {
        it->second.close();
    }
    m_sessions.clear();
}
