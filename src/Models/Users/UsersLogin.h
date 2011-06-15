#ifndef MODELS_USERS_LOGIN
#define MODELS_USERS_LOGIN

/// @file

#include <Generic/DB/Users/Users.h>
#include <Generic/IO/PIO/PIO.h>

namespace Models {
	namespace Users {
		/// User Login struct
		struct UsersLogin : public Models::Master::Master, public cppcms::form {
			cppcms::widgets::text login_username;     ///< Username
			cppcms::widgets::password login_password; ///< Password
			cppcms::widgets::submit login_submit;     ///< Submit button
			
			::Generic::IO::PIO pio; ///< PIO instance
			::Generic::DB::Users db; ///< Users instance
			
			std::string login_message; ///< Login message response
			UsersLogin() {
				login_submit.value("Login");
				*this + login_username + login_password + login_submit;
			}
			/// Validates user input
			///
			/// @return true if input is valid
			bool validate() {
				bool result = true;
				if (result && pio.wclength(login_username.value().c_str()) < 5) {
					login_message = "Username is shorter then 5 characters";
					result = false;
				}
				if (result && pio.wclength(login_username.value().c_str()) > 32) {
					login_message = "Username is longer then 32 characters";
					result = false;
				}
				if (result && pio.wclength(login_password.value().c_str()) < 5) {
					login_message = "Password is shorter then 5 characters";
					result = false;
				}
				if (result && pio.wclength(login_password.value().c_str()) > 32) {
					login_message = "Password is longer then 5 characters";
					result = false;
				}
				if (result && db.ExistUser(login_username.value(),login_password.value(),true)) {
					login_message = "Password is shorter then 5 characters";
					result = false;
				}
				return result;
			}
		};
	}
}


#endif
