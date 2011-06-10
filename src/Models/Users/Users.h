#ifndef RADIORANDOM_MODELS_USERS
#define RADIORANDOM_MODELS_USERS

/// @file

#include <Data/UserSet/UserSet.h>
#include <Helpers/Format/UserAccess.h>
#include <Data/Content/Content.h>


namespace model {
	/// USers model
	struct users :public master {
		string sortdir_username; ///< Username sort direction
		string sortdir_score;    ///< Score sort direction
		string sortdir_access;   ///< Access sort direction
		string sortdir_joined;   ///< Joined sort direction
		user_set usersset;       ///< Set of users
		Content content;	
		users() {
			sortdir_username = sortdir_score = sortdir_access = sortdir_joined = "desc";
		}
		/// User access format filter
		string user_access_filter(int access) {
			return format_access(access);
		}
	};

}

#endif

