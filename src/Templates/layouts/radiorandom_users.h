struct users :public master {
	std::string sort_username_dir;
	std::string sort_score_dir;
	std::string sort_access_dir;
	std::string sort_joined_dir;
	users_set usersset;
	users() {
		sort_username_dir = "desc";
		sort_score_dir = "desc";
		sort_access_dir = "desc";
		sort_joined_dir = "desc";
	}
	std::string time_passed(size_t time) {
		return format_time(time);
	}
};
