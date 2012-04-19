#include "manager.hpp"

void manager::mutex::lock(std::string const& name) {
    mutex_map::iterator it = m_mutex_map.find(name);
    booster::shared_ptr<cppdb::mutex> ptr;
    if (it == m_mutex_map.end()) {
        booster::shared_ptr<cppdb::mutex> mutex(new cppdb::mutex);
        m_mutex_map.insert(std::make_pair<std::string,booster::shared_ptr<cppdb::mutex> >(name,mutex));
        ptr = mutex;
    } else {
        ptr = it->second;
    }
    ptr->lock();
}

void manager::mutex::unlock(std::string const& name) {
    mutex_map::iterator it = m_mutex_map.find(name);
    if (it != m_mutex_map.end()) {
        it->second->unlock();
    }
}

void manager::mutex::unlock_all() {
    mutex_map::iterator it,end;
    end = m_mutex_map.end();
    for (it = m_mutex_map.begin(); it != end; ++it) {
        it->second->unlock();
    }
    m_mutex_map.clear();
}
