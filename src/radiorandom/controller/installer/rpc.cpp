#include "rpc.hpp"

// static

bool controller::installer_rpc::m_is_installing = false;
int controller::installer_rpc::m_current = 0;
int controller::installer_rpc::m_total = 0;

// public

controller::installer_rpc::installer_rpc(cppcms::service &srv)
    : generic_rpc(srv,"installer")
{
    mapper().assign("");
    bind("install_progress",json_method(&installer_rpc::install_progress,this),method_role);
}


void controller::installer_rpc::install_progress() {
    return_result("{ \"is_installing\" : "
                  + util::string::to_string(m_is_installing)
                  + ", \"total\" : "
                  + util::string::to_string(m_total)
                  + ", \"current\" : "
                  + util::string::to_string(m_current)
                  + " }");
}

int controller::installer_rpc::total() {
    return m_total;
}

void controller::installer_rpc::reset() {
    m_total = 0;
    m_current = 0;
}

void controller::installer_rpc::set_state(bool state) {
    m_is_installing = state;
}

void controller::installer_rpc::set_current(int count) {
    m_current = count;
}

void controller::installer_rpc::set_total(int count) {
    m_total = count;
}
