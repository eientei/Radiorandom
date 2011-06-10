#ifndef RADIORANDOM_MODELS_USERS_LOGIN
#define RADIORANDOM_MODELS_USERS_LOGIN

/// @file

#include <Data/UserSet/UserSet.h>
#include <Helpers/Auth/ValidUser.h>


namespace model {
	/// USers model
	struct users_login :public master, public cppcms::form {
		cppcms::widgets::text username;     ///< login
		cppcms::widgets::password password; ///< password
		cppcms::widgets::submit submit;     ///< submit button
		
		string message; ///< responce message
		bool result;    ///< result of validation
		users_login() {
			result = false;
			submit.value("Login");
			*this + username + password + submit;
		}
		/// Validates user input
		///
		/// @return bool
		virtual bool validate() {
			result = true;
			if (result && PString(username.value().c_str()).length() < 5) {
				message = "Username is lesser then 5 characters";
				result = false;
			}
			if (result && PString(username.value().c_str()).length() > 32) {
				message = "Username is longer then 32 characters";
				result = false;
			}
			if (result && PString(password.value().c_str()).length() < 5) {
				message = "Password is lesser then 5 characters";
				result = false;
			}
			if (result && PString(password.value().c_str()).length() > 32) {
				message = "Password is longer then 32 characters";
				result = false;
			}
			if (result && !valid_user(username.value(),password.value(),true)) {
				message = "Wrong login/password";
				result = false;
			}
			return result;	
		}
	};

}

#endif

