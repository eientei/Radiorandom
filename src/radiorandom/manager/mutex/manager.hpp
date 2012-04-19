#ifndef MANAGER_MUTEX_HPP
#define MANAGER_MUTEX_HPP

#include <string>
#include <map>

#include <booster/shared_ptr.h>
#include <cppdb/mutex.h>

namespace manager {
    class mutex {
        public:
            void lock(std::string const& name);
            void unlock(std::string const& name);
            void unlock_all();
        private:
            typedef std::map<std::string,booster::shared_ptr<cppdb::mutex> > mutex_map;
            mutex_map m_mutex_map;
    };
}

#endif // MANAGER_MUTEX_HPP
