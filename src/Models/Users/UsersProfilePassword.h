#ifndef MODELS_USERS_PROFILE_PASSWORD
#define MODELS_USERS_PROFILE_PASSWORD

/// @file

#include <Generic/IO/PIO/PIO.h>

namespace Models {
	namespace Users {
		/// Users password changing structure
		struct UsersProfilePassword : public Models::Master::Master, public cppcms::form {
			::Generic::IO::PIO pio; ///< PIO instance
			/// Password change to
			cppcms::widgets::password password;
			/// Password Confirmation
			cppcms::widgets::password password_confirmation;
			/// Submit button
			cppcms::widgets::submit submit;
			/// Response message
			std::string message;
			UsersProfilePassword() {
				submit.value("Change password");
				*this + password + password_confirmation + submit;
			}
			/// Validation function
			///
			/// @return true if input is valid
			bool validate() {
				bool result = true;
				if (result && pio.pio_wclength(password.value().c_str()) < 6) {
					message = "Password is shorter then 6 characters";
					result = false;
				}
				if (result && pio.pio_wclength(password.value().c_str()) > 32) {
					message = "Password is longer then 32 characters";
					result = false;
				}
				if (result && password.value() != password_confirmation.value()) {
					message = "Passwords do not match";
					result = false;
				}
				return result;
			}
		};
	}
}


#endif
/// @file
