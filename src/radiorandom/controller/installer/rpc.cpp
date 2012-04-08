#include "rpc.hpp"

controller::installer_rpc::installer_rpc(cppcms::service &srv)
    : generic_rpc(srv,"installer-rpc")
{
    m_is_installing = false;
    m_total_objects = 0;
    m_current_objects = 0;

    mapper().assign("");
    bind("install_progress",json_method(&controller::installer_rpc::install_progress,this),method_role);
}


void controller::installer_rpc::install_progress() {
    return_result("{ \"is_installing\" : "
                  + util::string::to_string(m_is_installing)
                  + ", \"total\" : "
                  + util::string::to_string(m_total_objects)
                  + ", \"current\" : "
                  + util::string::to_string(m_current_objects)
                  + " }");
}

void controller::installer_rpc::reset() {
    m_total_objects = 0;
    m_current_objects = 0;
}

void controller::installer_rpc::set_install_state(bool is_installing) {
    m_is_installing = is_installing;
}

void controller::installer_rpc::set_total_objects(int count) {
    m_total_objects = count;
}

void controller::installer_rpc::set_current_objects(int count) {
    m_current_objects = count;
}
