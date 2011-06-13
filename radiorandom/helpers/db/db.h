#ifndef RADIORANDOM_HELPERS_DB
#define RADIORANDOM_HELPERS_DB

#include <string>
#include <vector>
#include <stdio.h>
#include <radiorandom/db/db.h>
#include <radiorandom/helpers/format/format.h>

namespace helpers {
	class db {
		void sqlfy_pattern(std::string &s);
		std::string sqlfy_pseudo(cppdb::session &sql, const std::string &s, bool negate);
		std::string tags_parse(cppdb::session &sql, std::string url, std::string base, std::string table);
	};
}



#endif
