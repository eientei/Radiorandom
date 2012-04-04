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
