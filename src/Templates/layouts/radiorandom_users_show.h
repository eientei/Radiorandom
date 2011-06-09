struct users_show :public master {
	user_item user;
	std::string time_passed(size_t time) {
		return format_time(time);
	}
};
