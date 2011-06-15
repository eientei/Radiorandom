#include "SHA1.h"

size_t Generic::Hash::SHA1::GetHashSize() {
	return hash_size;
}

const unsigned char * Generic::Hash::SHA1::GetHash() {
	return hash;
}

Generic::Hash::SHA1::SHA1(std::string input) {
	::SHA1((unsigned char *)input.c_str(),input.length(),hash);
}

Generic::Hash::SHA1::SHA1(std::istream input) {
	char buf[8192];
	SHA_CTX sc;
	SHA1_Init(&sc);
	
	for (;;) {
		size_t len;
		len = input.readsome(buf,sizeof(buf));
		if (len == 0) break;
		SHA1_Update(&sc,buf,len);
	}
	SHA1_Final(hash,&sc);
}
