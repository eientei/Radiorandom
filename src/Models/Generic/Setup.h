#ifndef RADIORANDOM_MODELS_GENERIC_SETUP
#define RADIORANDOM_MODELS_GENERIC_SETUP

/// @file

namespace model {

	/// Setup model
	struct setup :public master, public cppcms::form  {
		cppcms::widgets::submit submit; ///< Submit button
		bool already_setted_up;         ///< Whether site were setted up
		setup() {
			submit.value("Setup");
			already_setted_up = false;
			*this + submit;
		}
	};

}

#endif

