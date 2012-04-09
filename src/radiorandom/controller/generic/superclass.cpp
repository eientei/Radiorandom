#include "superclass.hpp"

// static
//controller::app_manager controller::superclass::m_app;
controller::config_manager controller::superclass::m_config;
controller::mutex_manager controller::superclass::m_mutex;
//controller::rpc_manager controller::superclass::m_rpc;
controller::sql_manager controller::superclass::m_sql;

// public

controller::superclass::superclass() {

}

controller::superclass::~superclass() {

}

/*
controller::app_manager & controller::superclass::app() {
    return m_app;
}
*/

controller::config_manager & controller::superclass::config() {
    return m_config;
}

controller::mutex_manager & controller::superclass::mutex() {
    return m_mutex;
}
/*
controller::rpc_manager & controller::superclass::rpc() {
    return m_rpc;
}
*/
controller::sql_manager & controller::superclass::sql() {
    return m_sql;
}
