#include <radiorandom/helpers/filesystem/filesystem.h>

/// @file

bool helpers::filesystem::file_exists(std::string filepath) {
	struct stat filestatus;
	stat(filepath.c_str(),&filestatus);
	if (!S_ISREG(filestatus.st_mode)) {
		return false;
	}
	return true;
}
