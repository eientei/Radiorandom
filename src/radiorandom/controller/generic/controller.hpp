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

#include <radiorandom/wrapper/session/wrapper.hpp>

#include <radiorandom/util/fs/util.hpp>

#include "superclass.hpp"

namespace controller {
    class generic : public superclass, public cppcms::application {
        public:
            generic(cppcms::service & srv, std::string const& controller_name, std::string const& service_name = "   ");
            virtual ~generic();

            virtual void main(std::string url);
            virtual void index() = 0;

        protected:
            virtual void prepare(content::generic & c, std::string const& menu_item);
            void display(content::generic & c, std::string const& menu_item, std::string const& tmpl, std::string const& skin = "html");
            void please_install();
            void error(int code, std::string message = "");
            void do_dispatch(std::string const& url);
            void update_installed_state();
            static void sql_guard(wrapper::session & sql);
            static void sql_commit(wrapper::session & sql);
            wrapper::session & acquire_sql(bool is_static = false);

        private:
            void init_error_codes();
        private:
            static std::map<int,std::string> m_error_codes;
            static bool m_static_initalized;
        protected:
            wrapper::session m_sql;
    };
}


#endif // CONTROLLER_GENERIC_HPP
