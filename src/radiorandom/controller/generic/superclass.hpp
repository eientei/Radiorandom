#ifndef CONTROLLER_SUPERCLASS_HPP
#define CONTROLLER_SUPERCLASS_HPP

//#include <radiorandom/core/executor/core.hpp>

#include <cppcms/json.h>

#include <iostream>

#include <radiorandom/manager/mutex/manager.hpp>
#include <radiorandom/manager/sql/manager.hpp>

namespace controller {
    class superclass {
        public:
            superclass(std::string const& controller_type, std::string const& controller_name);
            virtual ~superclass();
            void set_config(cppcms::json::value const& value);
        public:
            static cppcms::json::value & config();
            static manager::mutex & mutex();
            static manager::sql   & sql();

        protected:
            std::string m_controller_type;
            std::string m_controller_name;

        private:
            static cppcms::json::value m_config;
            static manager::mutex m_mutex;
            static manager::sql   m_sql;
    };
}

#endif // CONTROLLER_SUPERCLASS_HPP
