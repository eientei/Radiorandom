#ifndef MODELS_USERS
#define MODELS_USERS

/// @file
#include <map>
#include <Generic/Data/Content/SetUsers/SetUsers.h>
#include <Generic/Markup/Navigation/Navigation.h>

namespace Models {
	namespace Users {
		/// Users struct.
		struct Users : public Models::Master::Master, public cppcms::form, public ::Generic::Data::Format, public ::Generic::Markup::Navigation {
			::Generic::Data::Content::SetUsers items;           ///< Users set
			
			cppcms::widgets::text search;     ///< search string
			cppcms::widgets::submit submit;     ///< submit button
			
			std::string what;
			
			
			std::string sort_directions_username; ///< Username sort direction
			std::string sort_directions_score;    ///< Score sort direction
			std::string sort_directions_access;   ///< Access sort direction
			std::string sort_directions_joined;   ///< Joined date sort direction
			Users() {
				submit.value("Search");
				*this + search + submit;
				sort_directions_username = "desc";
				sort_directions_score    = "desc";
				sort_directions_access   = "desc";
				sort_directions_joined   = "desc";
			}
		};
	}
}


#endif
