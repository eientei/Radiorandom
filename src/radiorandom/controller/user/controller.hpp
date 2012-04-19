#ifndef CONTROLLER_USER_HPP
#define CONTROLLER_USER_HPP

#include <radiorandom/controller/generic/controller.hpp>

#include <radiorandom/model/user/index.hpp>

#include <radiorandom/data/user/data.hpp>

#include <radiorandom/util/sql/util.hpp>

namespace controller {
    class user : public generic {
        public:
            user(cppcms::service & srv);
            virtual void index();
            virtual void foo();
        public:
            static void add_user(data::user const& user_data);
        private:
            static bool m_static_initialized;
            static cppdb::session m_sql_update;
    };
}


#endif // CONTROLLER_USER_HPP
