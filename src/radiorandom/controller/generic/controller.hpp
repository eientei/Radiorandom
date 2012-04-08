#ifndef CONTROLLER_GENERIC_HPP
#define CONTROLLER_GENERIC_HPP

#include <string>
#include <map>

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include <booster/shared_ptr.h>

#include <cppdb/frontend.h>
#include <cppdb/mutex.h>

#include <radiorandom/util/fs/util.hpp>

#include <radiorandom/model/generic/model.hpp>
#include <radiorandom/model/generic/error.hpp>
#include <radiorandom/model/generic/please_install.hpp>


namespace controller {
    class generic : public cppcms::application {
        public:
            generic(cppcms::service & srv, std::string const& module_name);
            virtual ~generic();

            bool is_installed();
            std::string const& lock_file();
            std::string const& schema_template();

            virtual void main(std::string url);
            virtual void index() = 0;

            static void lock(std::string const& name);
            static void unlock(std::string const& name);
            static void unlock_all();

            static void update(std::string const& stmt);
            static void update(std::istream & stream);

        protected:
            virtual void prepare(content::generic & c, std::string const& submodule_name);

            void please_install();
            void error(int code, std::string message = "");
            void display(content::generic & c, std::string const& tmpl, std::string const& skin = "html");
            void do_dispatch(std::string const& url);
            void update_installed_state();
        private:
            void init_error_codes();
            void init_static_context();
        protected:
            cppdb::session sql;
        private:
            typedef std::map<std::string,booster::shared_ptr<cppdb::mutex> >::iterator mutex_iterator;
            typedef std::map<std::string,booster::shared_ptr<cppdb::mutex> >::const_iterator mutex_const_iterator;
            static std::map<std::string,booster::shared_ptr<cppdb::mutex> > m_mutexes;
            static cppdb::session m_update_sql;
            static bool m_static_initialized;
            static bool m_is_installed;
            static std::string m_schema_template;
            static std::string m_connection_string;
            static std::string m_lock_file;
            static std::map<int,std::string> m_error_codes;

            std::string m_menu_item;
    };
}

#endif // CONTROLLER_GENERIC_HPP
