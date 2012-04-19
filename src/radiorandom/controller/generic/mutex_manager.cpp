#include "superclass.hpp"

void controller::mutex_manager::lock(std::string const& name) {
    mutex_map::iterator it = m_mutexes.find(name);
    booster::shared_ptr<cppdb::mutex> ptr;
    if (it == m_mutexes.end()) {
        booster::shared_ptr<cppdb::mutex> mutex(new cppdb::mutex);
        m_mutexes[name] = mutex;
        ptr = mutex;
    } else {
        ptr = it->second;
    }
    ptr->lock();
}

void controller::mutex_manager::unlock(const std::string &name) {
    mutex_map::iterator it = m_mutexes.find(name);
    if (it != m_mutexes.end()) {
        it->second->unlock();
    }
}

void controller::mutex_manager::unlock_all() {
    mutex_map::iterator it,end;
    end = m_mutexes.end();
    for (it = m_mutexes.begin(); it != end; ++it) {
        it->second->unlock();
    }
    m_mutexes.clear();
}
