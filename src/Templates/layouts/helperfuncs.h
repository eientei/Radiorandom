#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H

#include <gcrypt.h>
#include <cppdb/frontend.h>
#include <stdio.h>
#include <time.h>

std::string format_size(size_t size);
std::string format_time(size_t time);

char *sha1hash(const char *buf);

bool valid_user(std::string username, std::string password_hash, bool raw=false);

#endif
