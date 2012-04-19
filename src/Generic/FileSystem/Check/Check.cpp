#include "Check.h"


bool Generic::FileSystem::Check::ExistFile(std::string fpath) {
	if (fpath.empty()) fpath = filepath;
	struct stat filestatus;
	if (stat(fpath.c_str(),&filestatus) == -1)
		return false;
	if (S_ISREG(filestatus.st_mode)) {
		return true;
	}
	return false;
}
