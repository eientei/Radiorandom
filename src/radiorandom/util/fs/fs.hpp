/*
 * =====================================================================================
 *
 *       Filename:  fs.hpp
 *
 *    Description:  
 *
 *
 *        Version:  1.0
 *        Created:  28.03.2012 16:44:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tumin <itakingiteasy@gmail.com> Alexander (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef FS_HPP
#define FS_HPP

#include <string>
#include <fstream>

namespace util {
	namespace fs {
		bool file_exists(std::string const& filename);
		void create_file(std::string const& filename);
	}
}

#endif
