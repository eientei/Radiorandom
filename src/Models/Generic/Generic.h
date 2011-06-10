#ifndef RADIORANDOM_MODELS_GENERIC
#define RADIORANDOM_MODELS_GENERIC

/// @file

namespace model {

	/// Generic model
	struct generic :virtual public cppcms::base_content {
		bool setted_up; ///< whether site were setted up
		generic() {
			setted_up = false;
		}
	};

}
#endif

