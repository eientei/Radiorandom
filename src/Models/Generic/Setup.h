#ifndef MODELS_GENERIC_SETUP
#define MODELS_GENERIC_SETUP

/// @file

namespace Models {
	namespace Generic {
		/// Setup struct.
		/// Used to set web application up
		struct Setup : public Models::Master::Master, public cppcms::form {
			cppcms::widgets::submit setup_submit; ///< Submit button
			Setup() {
				setup_submit.value("Setup");
				*this + setup_submit;
			}
		};
	}
}


#endif
