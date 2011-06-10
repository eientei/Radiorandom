#ifndef RADIORANDOM_MODELS_USERS_PROFILE_PASSWORD
#define RADIORANDOM_MODELS_USERS_PROFILE_PASSWORD

/// @file

namespace model {
	/// Users profile password changing model
	struct users_profile_password :public master, public cppcms::form {
		cppcms::widgets::password password;              ///< Password field
		cppcms::widgets::password password_confirmation; ///< Password configrmation field
		cppcms::widgets::submit submit;            ///< Submit button
		string message;                            ///< Response message
		bool result;		                       ///< Result of operation
		users_profile_password() {
			result = false;
			submit.value("Change Confirmation");
			*this + password + password_confirmation + submit;
		}
		/// Validation routine
		virtual bool validate() {
			result = true;
			if (PString(password.value().c_str()).length() < 5) {
				message = "Password lesser then 5 characters";
				result = false;
			}
			if (PString(password.value().c_str()).length() > 32) {
				message = "Password longer then 32 characters";
				result = false;
			}
			if (result && password.value() != password_confirmation.value()) {
				message = "Passwords does not match";
				result = false;
			}
			return result;
		}
	};

}

#endif


