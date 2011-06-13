#ifndef RADIORANDOM_HELPERS_FILESYSTEM
#define RADIORANDOM_HELPERS_FILESYSTEM

/// @file

#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


namespace helpers {
	class filesystem {
		public:
			static bool file_exists(std::string filepath);
	};
}

#endif
