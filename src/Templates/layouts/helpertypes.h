class menu_item {
	public:
		std::string name;
		std::string href;
	public:
		menu_item() {
			name = href = "";
		}
		menu_item(std::string name, std::string href) {
			this->name = name;
			this->href = href;
		}
};

typedef std::vector<menu_item> links_set;


class user_item {
	public:
		int id;
		std::string username;
		int score;
		int access;
		size_t joined;
	public:
		user_item() {
			id = 0;
			username = "";
			score = -1;
			access = -1;
			joined = 0;
		}
		user_item(int id, std::string username, int score, int access, int joined) {
			this->id = id;
			this->username = username;
			this->score = score;
			this->access = access;
			this->joined = joined;
		}
};

typedef std::vector<user_item> users_set;

class post_item {
	public:
		std::string hash;
		std::string filename;
		std::string filepath;
		int score;
		int size;
		std::string tags;
		size_t posted;
	public:
		post_item() {
			hash = filename = filepath = tags = "";
			score = size = posted = 0;
		}
		post_item(std::string hash, std::string filename, std::string filepath, std:: string tags, int score, int size, size_t posted) {
			this->hash = hash;
			this->filename = filename;
			this->filepath = filepath;
			this->tags = tags;
			this->score = score;
			this->size = size;
			this->posted = posted;			
		}
};

typedef std::vector<post_item> posts_set;
