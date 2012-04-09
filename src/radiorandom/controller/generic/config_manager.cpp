#include "superclass.hpp"

controller::config_manager::property::property()
    : m_int_value(0), m_double_value(0), m_bool_value(false)
{ }

controller::config_manager::property & controller::config_manager::property::operator =(std::string const& data) {
    m_string_value = data;
    return *this;
}


controller::config_manager::property & controller::config_manager::property::operator =(int data) {
    m_int_value = data;
    return *this;
}

controller::config_manager::property & controller::config_manager::property::operator =(double data) {
    m_double_value = data;
    return *this;
}

controller::config_manager::property & controller::config_manager::property::operator =(bool data) {
    m_bool_value = data;
    return *this;
}


controller::config_manager::property::operator std::string() const {
    return m_string_value;
}

controller::config_manager::property::operator int() const {
    return m_int_value;
}

controller::config_manager::property::operator double() const {
    return m_double_value;
}

controller::config_manager::property::operator bool() const {
    return m_bool_value;
}


controller::config_manager::property & controller::config_manager::operator [](std::string const& key) {
    return m_properties[key];
}


controller::config_manager::property & controller::config_manager::set(std::string const& key) {
    return m_properties[key];
}





controller::config_manager::property & controller::config_manager::property::set(std::string const& data) {
    m_string_value = data;
    return *this;
}


controller::config_manager::property & controller::config_manager::property::set(int data) {
    m_int_value = data;
    return *this;
}

controller::config_manager::property & controller::config_manager::property::set(double data) {
    m_double_value = data;
    return *this;
}

controller::config_manager::property & controller::config_manager::property::set(bool data) {
    m_bool_value = data;
    return *this;
}
