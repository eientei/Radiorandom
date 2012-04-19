#include "wrapper.hpp"

wrapper::session::session() {
    m_name = "global";
}


wrapper::session::session(std::string const& name, bool is_static) {
    m_name = name;
    if (is_static) {
        m_name += "_static";
    }
}

std::string const& wrapper::session::name() {
    return m_name;
}
