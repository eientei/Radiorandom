/*
 * =====================================================================================
 *
 *       Filename:  string.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28.03.2012 18:43:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tumin <itakingiteasy@gmail.com> Alexander (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <string.h>

namespace util {
	namespace string {
		bool starts_with(std::string what, std::string with);
	}
}

#endif
