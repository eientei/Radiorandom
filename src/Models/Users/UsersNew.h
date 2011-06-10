#ifndef RADIORANDOM_MODELS_USERS_NEW
#define RADIORANDOM_MODELS_USERS_NEW

/// @file

#include <Data/PString/PString.h>
#include <cppdb/frontend.h>


namespace model {
	/// Users new model
	struct users_new :public master, public cppcms::form {
		cppcms::widgets::submit submit;                  ///< submit button
		cppcms::widgets::text username;                  ///< username field
		cppcms::widgets::email email;                    ///< email field
		cppcms::widgets::email email_confirmation;       ///< email configrmation field
		cppcms::widgets::password password;              ///< password field
		cppcms::widgets::password password_confirmation; ///< password confirmation field
		cppcms::widgets::checkbox tos;                   ///< TOS acceptance checkbox
		
		string username_message;              ///< username reply
		string password_message;              ///< password reply
		string password_confirmation_message; ///< confirmation reply
		string email_message;                 ///< email reply
		string email_confirmation_message;    ///< confirmation reply
		
		bool result; ///< whether form filled correctly
		
		users_new() {
			result = false;
			submit.value("Register");
			*this + username + email + email_confirmation + password + password_confirmation + tos + submit;
		}
		/// Validator
		virtual bool validate() {
			result = true;
			if (PString(username.value().c_str()).length() < 5) {
				username_message = "lesser then 5 characters";
				result = false;
			}
			if (PString(username.value().c_str()).length() > 32) {
				username_message = "longer then 32 characters";
				result = false;
			}
			if (!email.validate()) {
				email.error_message("");
				email_message = "invalid";
				result = false;
			}
			if (email.value() != email_confirmation.value()) {
				email_confirmation_message = "does not match";
				result = false;
			}
			if (PString(password.value().c_str()).length() < 5) {
				password_message = "lesser then 5 characters";
				result = false;
			}
			if (PString(password.value().c_str()).length() > 32) {
				password_message = "longer then 32 characters";
				result = false;
			}
			if (password.value() != password_confirmation.value()) {
				password_confirmation_message = "does not match";
				result = false;
			}
			if (!tos.value()) result = false;
			
			cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
			cppdb::result users = radiorandom_sql << "select count(*) from users where username = ?" << username.value();
			users.next();
			if (users.get<int>(0) != 0) {
				username_message += " Such username already exists";
				result = false;
			}
			
			return result;
		}

	};

}

#endif

