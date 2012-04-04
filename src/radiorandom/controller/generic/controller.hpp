#ifndef CONTROLLER_GENERIC_HPP
#define CONTROLLER_GENERIC_HPP

#include <string>
#include <map>

#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include <cppdb/frontend.h>

#include <radiorandom/model/generic/model.hpp>
#include <radiorandom/model/generic/error.hpp>
#include <radiorandom/model/generic/please_install.hpp>

#include <radiorandom/util/util.hpp>
#include <radiorandom/single/single.hpp>

namespace controller {
    class generic : public cppcms::application {
            std::string m_menu_item;
            std::map<int,std::string> m_error_codes;
            std::string m_lock_file;
            bool m_is_installed;
        protected:
            cppdb::session sql;
        public:
            generic(cppcms::service & srv, std::string module_name);
            ~generic();

            bool is_installed();
            std::string lock_file();

            virtual void main(std::string url);
            virtual void index() = 0;

        protected:
            virtual void prepare(content::generic & c, std::string submenu_item);

            void please_install();
            void error(int code, std::string message = "");
            void display(content::generic & c, std::string tmpl, std::string skin = "html");
            void do_dispatch(std::string url);
            void update_is_installed();

        private:
            void init_error_codes();

    };
}

#endif // CONTROLLER_GENERIC_HPP
