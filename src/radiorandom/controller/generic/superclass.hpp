#ifndef SUPERCLASS_HPP
#define SUPERCLASS_HPP

#include <string>
#include <vector>
#include <map>

#include <booster/shared_ptr.h>

#include <cppdb/frontend.h>
#include <cppdb/mutex.h>

#include <cppcms/service.h>
#include <cppcms/json.h>
#include <cppcms/rpc_json.h>


namespace controller {
    class mutex_manager {
        public:
            void lock(std::string const& name);
            void unlock(std::string const& name);
            void unlock_all();
        private:
            typedef std::map<std::string,booster::shared_ptr<cppdb::mutex> > mutex_map;
             mutex_map m_mutexes;
    };

    class rpc_manager {
        public:
            template <class T>
            booster::shared_ptr<T> acquire(std::string const& key, cppcms::service & srv);
            template <class T>
            booster::shared_ptr<T> operator[](std::string const& key);
        private:
            std::map<std::string,booster::shared_ptr<cppcms::rpc::json_rpc_server> > m_rpc;
    };


    class app_manager {
        public:
            template <class T>
            booster::shared_ptr<T> acquire(std::string const& key, cppcms::service & srv);
            template <class T>
            booster::shared_ptr<T> operator[](std::string const& key);
        private:
            std::map<std::string,booster::shared_ptr<cppcms::application> > m_app;

    };

    class config_manager {
        public:
            class property {
                public:
                    property();

                    property & operator =(std::string const& data);
                    property & operator =(int data);
                    property & operator =(double data);
                    property & operator =(bool data);
                    operator std::string() const;
                    operator int() const;
                    operator double() const;
                    operator bool() const;
                    property & set(std::string const& data);
                    property & set(int data);
                    property & set(double data);
                    property & set(bool data);

                private:
                    std::string m_string_value;
                    int m_int_value;
                    double m_double_value;
                    bool m_bool_value;
            };
            property & operator[](std::string const& key);
            template <typename T>
            T get(std::string const& key) {
                return (T)(m_properties[key]);
            }

            property & set(std::string const& key);
        private:
            std::map<std::string,property> m_properties;
    };

    class sql_manager {
        public:
            cppdb::session & session(std::string const& key);
            void close(std::string const& key);
            void close_all();
        private:
            std::map<std::string,cppdb::session> m_sessions;
    };


    class superclass {
        public:
            superclass();
            virtual ~superclass();

            //static app_manager & app();
            static config_manager & config();
            static mutex_manager & mutex();
            //static rpc_manager & rpc();
            static sql_manager & sql();
        private:
            //static app_manager m_app;
            static config_manager m_config;
            static mutex_manager m_mutex;
            //static rpc_manager m_rpc;
            static sql_manager m_sql;
    };
}


#endif // SUPERCLASS_HPP
