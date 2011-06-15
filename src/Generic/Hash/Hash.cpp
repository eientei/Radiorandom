#include "Hash.h"

std::string Generic::Hash::Hash::str() {
	std::string result;
	const unsigned char *	raw_hash = GetHash();
	for (size_t i=0; i < GetHashSize(); i++) {
		char literal[3];
		snprintf(literal,3,"%02x",raw_hash[i]);
		result += literal;
	}
	return result;
}
