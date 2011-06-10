#ifndef RADIORANDOM_HELPERS_FORMAT_FILESIZE
#define RADIORANDOM_HELPERS_FORMAT_FILESIZE

/// @file

#include <string>
#include <stdio.h>

using namespace std;

/// Formats size to human-readable format
///
/// \param [in] size of file format to
/// @return string represing file size
string format_filesize(size_t size);

#endif
