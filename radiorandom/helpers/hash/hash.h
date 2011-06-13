#ifndef RADIORANDOM_HELPERS_HASH
#define RADIORANDOM_HELPERS_HASH

/// @file

#include <string>
#include <openssl/sha.h>
#include <stdio.h>


namespace helpers {
	class hash {
		public:
			static std::string sha1hash_buf(std::string buffer);
			static std::string sha1hash_file(std::string filepath);
	};
}

#endif
