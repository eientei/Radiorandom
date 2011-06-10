#include <Helpers/FileSystem/FileExists.h>

bool file_exists(string setuplock) {
	struct stat filestatus;
	stat(setuplock.c_str(),&filestatus);
	if (!S_ISREG(filestatus.st_mode)) {
		return false;
	}
	return true;
}
