struct posts :public master {
	std::string sort_filename_dir;
	std::string sort_score_dir;
	std::string sort_tags_dir;
	std::string sort_size_dir;
	std::string sort_posted_dir;
	posts_set postsset;
	bool many;
	int page;
	int total;
	int pagesize;
	std::string prefix;
	std::string suffix;
	posts() {
		sort_filename_dir = "desc";
		sort_score_dir = "desc";
		sort_tags_dir = "desc";
		sort_size_dir = "desc";
		sort_posted_dir = "desc";
		
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
	std::string formatsize(size_t size) {
		return format_size(size);
	}
};
