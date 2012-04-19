#include "superclass.hpp"

// static
cppcms::json::value controller::superclass::m_config;
manager::mutex controller::superclass::m_mutex;
manager::sql   controller::superclass::m_sql;

// public

controller::superclass::superclass(std::string const& controller_type, std::string const& controller_name) {
    m_controller_type = controller_type;
    m_controller_name = controller_name;
    std::cout << "  " << m_controller_type << " [NEW]  " << m_controller_name << std::endl;
}

controller::superclass::~superclass() {
    std::cout << "  " << m_controller_type << " [DEL]  " << m_controller_name << std::endl;
}

void controller::superclass::set_config(cppcms::json::value const& value) {
    m_config = value;
}

cppcms::json::value & controller::superclass::config() {
    return m_config;
}

manager::mutex & controller::superclass::mutex() {
    return m_mutex;
}

manager::sql & controller::superclass::sql() {
    return m_sql;
}
