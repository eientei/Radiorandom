struct index :public master {
	size_t files;
	size_t filessize;
	std::string format_filessize(size_t size) {
		return format_size(size);
	}
};
