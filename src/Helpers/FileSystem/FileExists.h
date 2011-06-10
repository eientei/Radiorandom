#ifndef RADIORANDOM_HELPERS_FILESYSTEM_FILEEXISTS
#define RADIORANDOM_HELPERS_FILESYSTEM_FILEEXISTS

#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

bool file_exists(string setuplock);

#endif
