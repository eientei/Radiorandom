#ifndef MODELS_MASTER_GENERIC
#define MODELS_MASTER_GENERIC

/// @file

#include <cppcms/view.h>

#include <Generic/Data/Content/SetUsers/SetUsers.h>

namespace Models {
	namespace Master {
		/// Generic model. 
		/// Used for all other models directly or not.
		struct Generic : public cppcms::base_content{
			bool generic_setted_up;       ///< If site were setted up
			::Generic::Data::Content::SetUsers::ItemUser user; ///< User data
			Generic() {
				generic_setted_up = false;
			}
		};
	}
}

#endif
