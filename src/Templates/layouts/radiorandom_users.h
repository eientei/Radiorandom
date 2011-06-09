struct users :public master {
	std::string sort_username_dir;
	std::string sort_score_dir;
	std::string sort_access_dir;
	std::string sort_joined_dir;
	users_set usersset;
	bool many;
	int page;
	int total;
	int pagesize;
	std::string prefix;
	std::string suffix;
	users() {
		sort_username_dir = "desc";
		sort_score_dir = "desc";
		sort_access_dir = "desc";
		sort_joined_dir = "desc";
		
		prefix="";
		suffix="";
		
		many = false;
		page = 1;
		total = 0;
		pagesize = 1;
	}
	std::string time_passed(size_t time) {
		return format_time(time);
	}
	std::string navigation_gen(size_t page) {
		return navigation_generator(prefix, page,pagesize,total);
	}
};
