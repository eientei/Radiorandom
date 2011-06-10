#ifndef RADIORANDOM_MODELS_GENERIC_ERROR
#define RADIORANDOM_MODELS_GENERIC_ERROR

/// @file

namespace model {

	/// Error model
	struct error :public master {
		int errorcode; ///< Error code to display
		error() {
			errorcode = 404;
		}
	};

}

#endif

