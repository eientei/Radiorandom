struct posts_new :public master, public cppcms::form {
	cppcms::widgets::file file;
	cppcms::widgets::textarea tags;
	cppcms::widgets::submit submit;
	std::string message;
	std::string thanks;
	bool exists;
	std::string exists_filename;
	std::string exists_filepath;
	int exists_size;
	int exists_score;
	std::string exists_tags;
	int exists_posted;
	posts_new() {
		submit.value("Upload");
		*this + file + tags + submit;
		exists = false;
	}
	std::string time_passed(size_t time) {
		return format_time(time);
	}
	std::string formatsize(size_t size) {
		return format_size(size);
	}
	
};
