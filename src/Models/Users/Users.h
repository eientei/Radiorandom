#ifndef MODELS_USERS
#define MODELS_USERS

/// @file
#include <map>
#include <Generic/Data/Content/SetUsers/SetUsers.h>

namespace Models {
	namespace Users {
		/// Users struct.
		struct Users : public Models::Master::Master/*, public Helpers::Format*/ {
			::Generic::Data::Content::SetUsers users_set;           ///< Users set
			::Generic::Data::Format formatter; ///< Formatter instance
			
			std::string sort_directions_username; ///< Username sort direction
			std::string sort_directions_score;    ///< Score sort direction
			std::string sort_directions_access;   ///< Access sort direction
			std::string sort_directions_joined;   ///< Joined date sort direction
			Users() {
				sort_directions_username = "desc";
				sort_directions_score    = "desc";
				sort_directions_access   = "desc";
				sort_directions_joined   = "desc";
			}
		};
	}
}


#endif
