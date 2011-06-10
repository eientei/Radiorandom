#ifndef RADIORANDOM_HELPERS_VALID_MAKESESSION
#define RADIORANDOM_HELPERS_VALID_MAKESESSION

#include <string>

#include <Helpers/Hash/SHA1.h>
#include <cppdb/frontend.h>

/// @file

using namespace std;

/// Checks if session in cookie is valid
///
/// \param [in] session to check
/// @return username or ""
string make_session(string username);

#endif

