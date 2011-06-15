#ifndef MODELS_USERS_PROFILE_EMAIL
#define MODELS_USERS_PROFILE_EMAIL

/// @file

namespace Models {
	namespace Users {
		/// Profile email changing struct
		struct UsersProfileEmail : public Models::Master::Master, public cppcms::form  {
			/// Email change to
			cppcms::widgets::email email;
			/// Confirmation of input
			cppcms::widgets::email email_confirmation;
			/// SUbmit button
			cppcms::widgets::submit submit;
			/// Response message
			std::string profile_email_message;
			UsersProfileEmail() {
				submit.value("Change Email");
				*this + email + email_confirmation + submit;
			}
			/// Validation fuinction
			///
			/// @return true on valid data
			bool validation() {
				bool result = true;
				if (result && !email.validate()) {
					email.error_message("");
					profile_email_message = "Invalid email";
					result = false;
				}
				if (result && email_confirmation.value() != email.value()) {
					profile_email_message = "Emails do not match";
					result = false;
				}
				return result;
			}
		};
		
	}
}


#endif
