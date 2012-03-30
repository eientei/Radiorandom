/*
 * =====================================================================================
 *
 *       Filename:  string.cpp
 *
 *    Description:  
 *
 *
 *        Version:  1.0
 *        Created:  28.03.2012 18:44:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tumin <itakingiteasy@gmail.com> Alexander (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "string.hpp"

bool util::string::starts_with(std::string what, std::string with) {
	size_t what_len = what.length();
	size_t with_len = with.length();
	size_t len = what_len;
	if (with_len < what_len) len = with_len;
	if (len == 0) return false;
	return strncmp(what.c_str(), with.c_str(), len) == 0;
}
