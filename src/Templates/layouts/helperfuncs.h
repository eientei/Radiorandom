#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H

#include <gcrypt.h>
#include <cppdb/frontend.h>
#include <stdio.h>
#include <time.h>

std::string format_size(size_t size);
std::string format_time(size_t time);
std::string navigation_generator(std::string prefix, int page, int pagesize, int total);

std::string sha1hash(std::string buf);

bool valid_user(std::string username, std::string password_hash, bool raw=false);
std::string make_session(std::string username);

#endif
