#ifndef RADIORANDOM_MODELS_USERS_PROFILE_EMAIL
#define RADIORANDOM_MODELS_USERS_PROFILE_EMAIL

/// @file

namespace model {
	/// Users profile email changing model
	struct users_profile_email :public master, public cppcms::form {
		cppcms::widgets::email email;              ///< Email field
		cppcms::widgets::email email_confirmation; ///< Email configrmation field
		cppcms::widgets::submit submit;            ///< Submit button
		string message;                            ///< Response message
		string current_email;                      ///< Current email
		bool result;		                       ///< Result of operation
		users_profile_email() {
			result = false;
			submit.value("Change Email");
			*this + email + email_confirmation + submit;
		}
		/// Validation routine
		virtual bool validate() {
			result = true;
			if (!email.validate()) {
				email.error_message("");
				message = "Invalid email";
				result = false;
			}
			if (result && email.value() != email_confirmation.value()) {
				message = "Emails does not match";
				result = false;
			}
			return result;
		}
	};

}

#endif


