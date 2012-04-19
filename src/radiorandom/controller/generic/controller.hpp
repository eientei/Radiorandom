#ifndef CONTROLLER_GENERIC_HPP
#define CONTROLLER_GENERIC_HPP

#include <map>
#include <string>

#include <cppcms/application.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include <radiorandom/model/generic/model.hpp>
#include <radiorandom/model/generic/error.hpp>
#include <radiorandom/model/generic/please_install.hpp>

#include <radiorandom/util/fs/util.hpp>

#include "superclass.hpp"

namespace controller {
    class generic : public superclass, public cppcms::application {
        public:
            generic(cppcms::service & srv, std::string const& module_name);
            virtual ~generic();

            virtual void main(std::string url);
            virtual void index() = 0;

        protected:
            virtual void prepare(content::generic & c, std::string const& submodule_name);
            void please_install();
            void error(int code, std::string message = "");
            void display(content::generic & c, std::string const& tmpl, std::string const& skin = "html");
            void do_dispatch(std::string const& url);
            void update_installed_state();
            static void sql_update_lock(std::string const& module_name);
            static void sql_update_unlock(std::string const& module_name);
            cppdb::session acquire_static_sql();

        private:
            void init_error_codes();

        private:
            static std::map<int,std::string> m_error_codes;
            static bool m_static_initialized;
        protected:
            cppdb::session m_sql;
            std::string m_module_name;
    };
}

#endif // CONTROLLER_GENERIC_HPP
