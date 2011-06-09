struct setup :public master, public cppcms::form {
	cppcms::widgets::submit submit;
	bool already_setted_up;
	setup() {
		submit.value("Setup");
		already_setted_up = false;
		*this + submit;
	}
};
