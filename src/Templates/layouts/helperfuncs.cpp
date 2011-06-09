#include "helperfuncs.h"

std::string format_size(size_t size) {
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

std::string format_time(size_t t) {
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

char *sha1hash(const char *buf) {
	int input_len = strlen(buf);
	int hash_len = gcry_md_get_algo_dlen(GCRY_MD_SHA1);
	unsigned char *binary_hash = new unsigned char[hash_len];
	char *textual_hash = new char[hash_len * 2 + 1];
	char *p = textual_hash;
	gcry_md_hash_buffer(GCRY_MD_SHA1,binary_hash,buf,input_len);
	for (int i=0; i < hash_len; i++, p+=2) {
		snprintf(p,3,"%02x",binary_hash[i]);
	}
	delete[] binary_hash;   
	return textual_hash;
}

bool valid_user(std::string username, std::string password_hash, bool raw) {
	const char *hash;
	if (raw) {
		hash = sha1hash(password_hash.c_str());
	} else {
		hash = password_hash.c_str();
	}
	cppdb::session users_sql("sqlite3:db=db/users.db");
	cppdb::result users = users_sql << "select count(*) from users where username = ? and password_hash = ?" << username << password_hash;
	users.next();
	if (raw) delete[] hash;
	return users.get<int>(0) == 1;
}
