#include "Format.h"



std::string Generic::Data::Format::FileSize(int size) {
	float fsize = size;
	std::string suffix("B");
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
	
	
	return ToString(fsize) + " " + suffix;
}


std::string Generic::Data::Format::TimePassed(int t) {
	std::string suffix = "seconds";
	int current_time = time(NULL);
	int diff = (current_time - t);
	if (diff > 60) {
		diff /= 60;
		suffix = "minutes";
		if (diff == 1) suffix = "minute";
		if (diff > 60) {
			diff /= 60;
			suffix = "hours";
			if (diff == 1) suffix = "hour";
			if (diff > 24) {
				diff /= 24;
				suffix = "days";
				if (diff == 1) suffix = "day";
				if (diff > 30) {
					diff /= 30;
					suffix = "months";
					if (diff == 1) suffix = "month";
					if (diff > 12) {
						diff /= 12;
						suffix = "years";
						if (diff == 1) suffix = "year";
					}
				}
			}
		}
	}
	return ToString(diff) + " " + suffix + " ago";
}


std::string Generic::Data::Format::URIUnEscape(std::string uri) {
	char *buf = new char[uri.length() + 1];
	strncpy(buf,uri.c_str(),uri.length());
	buf[uri.length()] = '\0';
	uriUnescapeInPlaceA(buf);
	std::string result(buf);
	delete[] buf;
	return result;
}


std::string Generic::Data::Format::UserAccessFormat(int access) {
	//Helpers::DB.Format.PopulateAccessLevel(user_access_levels);
	return user_access_levels[access];
	
}
