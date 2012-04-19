#include "core.hpp"

executor::already_running::already_running()
    : runtime_error("Application is already running!")
{ }

executor::already_running::already_running(std::string const& message)
    : runtime_error(message)
{ }
