#ifndef RADIORANDOM_HELPERS_HASH_SHA1
#define RADIORANDOM_HELPERS_HASH_SHA1

#include <string>
#include <openssl/sha.h>
#include <stdio.h>

using namespace std;

string sha1hash_buf(string buffer);
string sha1hash_file(string filepath);

#endif
