struct users_profile_password :public master, public cppcms::form {
	cppcms::widgets::password password;
	cppcms::widgets::password password_confirmation;
	cppcms::widgets::submit submit;
	std::string message;
	bool result;
	
	users_profile_password() {
		submit.value("Change Password");
		*this + password + password_confirmation + submit;
		result = true;
	}
	virtual bool validate() {
		if (PString(password.value().c_str()).length() < 5) {
			message = "lesser then 5 characters";
			result = false;
		}
		if (PString(password.value().c_str()).length() > 32) {
			message = "longer then 32 characters";
			result = false;
		}
		if (password.value() != password_confirmation.value()) {
			message = "does not match";
			result = false;
		}
		return result;
	}
};

