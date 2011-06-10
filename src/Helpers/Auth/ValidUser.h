#ifndef RADIORANDOM_HELPERS_VALID_USER
#define RADIORANDOM_HELPERS_VALID_USER

#include <string>
#include <cppdb/frontend.h>
#include <Helpers/Hash/SHA1.h>

/// @file

using namespace std;

/// Validates user by given login/password[hash]
bool valid_user(string username, string password_hash, bool raw = false);

#endif
