#include "core.hpp"


executor::configuration_parse_error::configuration_parse_error()
    : runtime_error("Configuratin parse error")
{ }


executor::configuration_parse_error::configuration_parse_error(std::string const& message)
    : runtime_error(message)
{ }

executor::configuration_parse_error::configuration_parse_error(std::string const& file, int line_no)
    : runtime_error("Configuration parse error in file `" + file + "' at line no " + util::string::to_string(line_no))
{ }
