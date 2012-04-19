#include "wrapper.hpp"

wrapper::sql::session::session(std::string const& name, bool is_static) {
    m_name = name;
    m_is_static = is_static;
}
