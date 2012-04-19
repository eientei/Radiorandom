#ifndef MODELS_USERS_LOGIN
#define MODELS_USERS_LOGIN

/// @file

#include <Generic/DB/Users/Users.h>
#include <Generic/IO/PIO/PIO.h>

namespace Models {
	namespace Users {
		/// User Login struct
		struct UsersLogin : public Models::Master::Master, public cppcms::form {
			cppcms::widgets::text username;     ///< Username
			cppcms::widgets::password password; ///< Password
			cppcms::widgets::submit submit;     ///< Submit button
			
			::Generic::IO::PIO pio; ///< PIO instance
			::Generic::DB::Users db; ///< Users instance
			
			std::string message; ///< Login message response
			UsersLogin() {
				submit.value("Login");
				*this + username + password + submit;
			}
			/// Validates user input
			///
			/// @return true if input is valid
			bool validate() {
				bool result = true;
				if (result && pio.pio_wclength(username.value().c_str()) < 5) {
					message = "Username is shorter then 5 characters";
					result = false;
				}
				if (result && pio.pio_wclength(username.value().c_str()) > 32) {
					message = "Username is longer then 32 characters";
					result = false;
				}
				if (result && pio.pio_wclength(password.value().c_str()) < 5) {
					message = "Password is shorter then 5 characters";
					result = false;
				}
				if (result && pio.pio_wclength(password.value().c_str()) > 32) {
					message = "Password is longer then 5 characters";
					result = false;
				}
				if (result && !db.ExistUser(username.value(),password.value(),true)) {
					message = "Wrong login/password";
					result = false;
				}
				return result;
			}
		};
	}
}


#endif
