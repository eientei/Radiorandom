#ifndef RADIORANDOM_MODELS_USERS_CONTENT
#define RADIORANDOM_MODELS_USERS_CONTENT

#include <radiorandom/data/data.h>


namespace models {
namespace users {
	struct content :virtual public models::master::master {
		std::string content_sortdir_name;
		std::string content_sortdir_score;
		std::string content_sortdir_access;
		std::string content_sortdir_joined;
		
		data::content::user_set users;
		content() {
			content_sortdir_name = "desc";
			content_sortdir_score = "desc";
			content_sortdir_access = "desc";
			content_sortdir_joined = "desc";
		}
	};
}
}


#endif
