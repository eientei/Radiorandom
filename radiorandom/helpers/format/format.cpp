#include <radiorandom/helpers/format/format.h>

std::map<int,std::string> helpers::format::accesses;
std::map<std::string,int> helpers::format::values;

/// @file

std::string helpers::format::time_passed(int t) {
	char buf[1024];
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
	snprintf(buf,1024,"%d",diff);
	return buf + std::string(" ") + suffix + " ago";
}

std::string helpers::format::uri_unescape(std::string uri) {
	char *buf = new char[uri.length() + 1];
	strncpy(buf,uri.c_str(),uri.length());
	buf[uri.length()] = '\0';
	uriUnescapeInPlaceA(buf);
	std::string result(buf);
	delete[] buf;
	return result;
}


void helpers::format::populate_accesses() {
	if (accesses.size() == 0) {
		db::result access = db::sql() << "select * from access_levels";	
		while(access.next()) {
			accesses[access.get<int>("value")] = access.get<std::string>("name");
			values[access.get<std::string>("name")] = access.get<int>("value");
		}
	}
}

std::string helpers::format::user_access_format(int level) {
	populate_accesses();
	return accesses[level];
	
}

int helpers::format::user_access_unformat(std::string access) {
	populate_accesses();
	return values[access];
}


std::string helpers::format::file_size(size_t size) {
	char buf[1024];
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
	snprintf(buf,1024,"%.2f",fsize);
	
	return buf + std::string(" ") + suffix;
}
