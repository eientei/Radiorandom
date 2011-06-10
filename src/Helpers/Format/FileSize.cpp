#include <Helpers/Format/FileSize.h>

/// @file

string format_filesize(size_t size) {
	char buf[1024];
	float fsize = size;
	string suffix("B");
	if (size / 1024 > 0) {
		suffix = "KB";
		size /= 1024;
		fsize /= 1024;
	}
	if (size / 1024 > 0) {
		suffix = "MB";
		size /= 1024;
		fsize /= 1024;
	}
	if (size / 1024 > 0) {
		suffix = "GB";
		size /= 1024;
		fsize /= 1024;
	}
	if (size / 1024 > 0) {
		suffix = "TB";
		size /= 1024;
		fsize /= 1024;
	}
	snprintf(buf,1024,"%.2f",fsize);
	
	return buf + string(" ") + suffix;
}
