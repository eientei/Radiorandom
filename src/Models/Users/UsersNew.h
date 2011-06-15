#ifndef MODELS_USERS_NEW
#define MODELS_USERS_NEW

/// @file

#include <Generic/IO/PIO/PIO.h>

namespace Models {
	namespace Users {
		/// New user structure
		struct UsersNew : public Models::Master::Master, public cppcms::form {
			
			::Generic::IO::PIO pio; ///< PIO instance
			
			/// Username field
			cppcms::widgets::regex_field username;
			
			/// Email field
			cppcms::widgets::email email;
			
			/// Email confirmation field
			cppcms::widgets::email email_confirmation;
			
			/// Password field
			cppcms::widgets::password password;
			
			/// Password confirmation field
			cppcms::widgets::password password_confirmation;
			
			/// Acceptance of TOS chechbox
			cppcms::widgets::checkbox acceptance_of_tos;
			
			/// Submit button
			cppcms::widgets::submit submit;
			
			/// Username response message
			std::string username_message;
			
			/// Password response message
			std::string password_message;
			
			/// Password confirmation response message
			std::string password_confirmation_message;
			
			/// Email response message
			std::string email_message;
			
			/// Email configrmation response message
			std::string email_confirmation_message;
			UsersNew() {
				submit.value("Register");
				username.regex(std::string("[^:*%]{5,32}"));
				*this + username + email + email_confirmation + password + password_confirmation + acceptance_of_tos + submit;
			}
			/// Validation function
			///
			/// @return true if input is valid
			bool validate() {
				bool result = true;
				if (pio.wclength(username.value().c_str()) < 5) {
					username_message = "shorter then 5 characters";
					result = false;
				}
				if (pio.wclength(username.value().c_str()) > 32) {
					username_message = "longer then 32 characters";
					result = false;
				}
				if (!username.validate()) {
					username.error_message("");
					username_message = "Username may not contain any of *, : or % characters";
					result = false;
				}
				if (pio.wclength(password.value().c_str()) < 6) {
					password_message = "shorter then 6 characters";
					result = false;
				}
				if (pio.wclength(password_confirmation.value().c_str()) > 32) {
					password_message = "longer then 32 characters";
					result = false;
				}
				if (password_confirmation.value() != password.value()) {
					password_confirmation_message = "do not match";
					result = false;
				}
				if (!email.validate()) {
					email.error_message("");
					email_message = "invalid";
					result = false;
				}
				if (email.value() != email.value()) {
					email_confirmation_message = "do not match";
					result = false;
				}
				if (!acceptance_of_tos.value()) result = false;
				return result;
			}
		};
	}
}


#endif
