#ifndef RADIORANDOM_HELPERS_FORMAT
#define RADIORANDOM_HELPERS_FORMAT

#include <string>
#include <vector>
#include <map>
#include <radiorandom/db/db.h>
#include <stdio.h>
#include <string.h>
#include <uriparser/Uri.h>

namespace helpers {
	class format {
		private:
			static std::map<int,std::string> accesses;
			static std::map<std::string,int> values;
		public:
			static std::string time_passed(int t);
			static std::string uri_unescape(std::string uri);
			static std::string file_size(size_t size);
			static void populate_accesses();
			static std::string user_access_format(int level);
			static int user_access_unformat(std::string level);
	};

}



#endif
