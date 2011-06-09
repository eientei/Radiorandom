struct users_new :public master, public cppcms::form {
		cppcms::widgets::submit submit;
		cppcms::widgets::text username;
		cppcms::widgets::email email;
		cppcms::widgets::email email_confirmation;
		cppcms::widgets::password password;
		cppcms::widgets::password password_confirmation;
		cppcms::widgets::checkbox tos;
		
		std::string username_message;
		std::string password_message;
		std::string password_confirmation_message;
		std::string email_message;
		std::string email_confirmation_message;
		
		bool result;
		
		users_new() {
			result = false;
			submit.value("Register");
			email_message = email_confirmation_message = "";
			password_message = password_confirmation_message = "";
			username_message = "";
			*this + username + email + email_confirmation + password + password_confirmation + tos + submit;
		}
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
			}
			if (email.value() != email_confirmation.value()) {
				email_confirmation_message = "does not match";
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
			return result;
		}
};

