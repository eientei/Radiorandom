#include <radiorandom/helpers/hash/hash.h>

/// @file

std::string helpers::hash::sha1hash_buf(std::string buffer) {
	unsigned char outbuf[20];
	unsigned char hash_literal[128];
	SHA1((unsigned char*)buffer.c_str(),buffer.length(),outbuf);
	unsigned char *p=hash_literal;
	for (int i=0; i < 20; i++, p+=2) {
		snprintf((char *)p,3,"%02x",outbuf[i]);
	}
	
	return std::string((char *)hash_literal);
}
std::string helpers::hash::sha1hash_file(std::string filepath) {
		FILE *f;
		unsigned char buf[8192];
		unsigned char out[32];
		char hash[128];
		SHA_CTX sc;
		f = fopen(filepath.c_str(),"r");
		SHA1_Init(&sc);
		for (;;) {
			size_t len;
			len = fread(buf,1,sizeof buf,f);
			if (len == 0) break;
			SHA1_Update(&sc,buf,len);
		}
		fclose(f);
		SHA1_Final(out,&sc);
		char *p = hash;
		for (int i=0; i < 20; i++, p+=2) {
			snprintf(p,3,"%02x",out[i]);
		}
		return std::string(hash);
}
