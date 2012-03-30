/*
 * =====================================================================================
 *
 *       Filename:  fs.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28.03.2012 16:45:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tumin <itakingiteasy@gmail.com> Alexander (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "fs.hpp"


bool util::fs::file_exists(std::string const& path) {
	return std::ifstream(path.c_str()) != NULL;
}

void util::fs::create_file(std::string const& path) {
	std::ofstream target(path.c_str());
	target.close();
}
