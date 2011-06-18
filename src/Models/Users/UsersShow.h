#ifndef MODELS_USERS_SHOW
#define MODELS_USERS_SHOW

/// @file

#include <Generic/Data/Content/SetUsers/SetUsers.h>

namespace Models {
	namespace Users {
		/// Show specific user strucutre
		struct UsersShow : public Models::Master::Master, public ::Generic::Data::Format {
			/// User item
			::Generic::Data::Content::SetUsers::ItemUser item;
		};
	}
}


#endif
/// @file
/// @file
