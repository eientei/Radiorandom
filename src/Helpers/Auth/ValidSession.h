#ifndef RADIORANDOM_HELPERS_VALID_SESSION
#define RADIORANDOM_HELPERS_VALID_SESSION

#include <cppdb/frontend.h>

#include <string>

/// @file

using namespace std;

/// Checks if session in cookie is valid
///
/// \param [in] session to check
/// @return username or ""
string valid_session(string session);

#endif
