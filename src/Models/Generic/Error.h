#ifndef MODELS_GENERIC_ERROR
#define MODELS_GENERIC_ERROR

/// @file

namespace Models {
	namespace Generic {
		/// Error struct.
		/// Used to show errors.
		struct Error : public Models::Master::Master {
			int error_code;            ///< Error code to be displayed
			std::string error_message; ///< Message to be displayed
			Error() {
				error_code = 0;
			}
		};
	}
}


#endif
