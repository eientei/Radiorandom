#ifndef RADIORANDOM_DATA_CONTENT_USERSET
#define RADIORANDOM_DATA_CONTENT_USERSET

#include <string>
#include <vector>


namespace data {
namespace content {
	class user_item {
		public:
			int id;
			int access;
			std::string name;
			std::string password_hash;
			std::string email;
			int joined;
			int score;
			int changer;
			int changed;
		public:
			user_item();
			user_item(
				int id, 
				int access, 
				std::string name, 
				std::string password_hash,
				std::string email,
				int joined,
				int score,
				int changer,
				int changed
			);
	};
	typedef std::vector<user_item> user_set;
}
}



#endif
