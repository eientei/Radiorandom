#ifndef GENERIC_HASH_HASH
#define GENERIC_HASH_HASH

/// @file

#include <string>
#include <stdio.h>


#include <Generic/Generic.h>

/// Generic Hash interface
class Generic::Hash::Hash {
	public:
		/// Get hash buffer size
		virtual size_t GetHashSize() = 0;
		
		/// Get hash buffer
		virtual const unsigned char * GetHash() = 0;
	public:
		/// Decorator interface
		std::string str();
};


#endif
