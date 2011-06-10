#ifndef RADIORANDOM_MODELS_USERS_SHOW
#define RADIORANDOM_MODELS_USERS_SHOW

/// @file

#include <Helpers/Format/UserAccess.h>


namespace model {
	/// USers model
	struct users_show :public master {
		string username; ///< Usernae
		int id;          ///< User id
		int score;       ///< User score
		int access;      ///< User access
		int joined;      ///< User join date
		users_show() {
			id = score = access = joined = 0;
		}
		/// User access format filter
		string user_access_filter(int access) {
			return format_access(access);
		}
	};

}

#endif

