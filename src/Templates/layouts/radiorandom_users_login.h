struct users_login :public master, public cppcms::form {
	cppcms::widgets::text username;
	cppcms::widgets::password password;
	cppcms::widgets::submit submit;
	
	std::string message;
	users_login() {
		submit.value("Login");
		*this + username + password + submit;
	}
};
