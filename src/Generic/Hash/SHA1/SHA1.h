#ifndef GENERIC_HASH_SHA1
#define GENERIC_HASH_SHA1

/// @file
#include <istream>
#include <string>

#include <openssl/sha.h>

#include <Generic/Generic.h>
#include <Generic/Hash/Hash.h>



/// Menu content data strcuture
class Generic::Hash::SHA1 : public Hash {
	private:
		/// binary Hash length
		const static size_t hash_size = 20;
		/// Hash holder
		unsigned char hash[hash_size];
	public:
		size_t GetHashSize();
		const unsigned char * GetHash();
		
		/// Constructor from string
		///
		/// \param [in] input to hash
		///
		/// @return hash string
		SHA1(std::string input);

		/// Constructor from istream
		///
		/// \param [in] input to hash
		///
		/// @return hash string
		SHA1(std::istream input);
};

#endif
