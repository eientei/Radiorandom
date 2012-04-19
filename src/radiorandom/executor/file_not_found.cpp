#include "core.hpp"

executor::file_not_found::file_not_found()
    : runtime_error("File not found")
{ }

executor::file_not_found::file_not_found(const std::string &file)
    : runtime_error("File not found: " + file)
{ }
