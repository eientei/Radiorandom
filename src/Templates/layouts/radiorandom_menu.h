struct menu :public cppcms::base_content {
	links_set menu_links_left;
	links_set menu_links_right;
	links_set submenu_links_left;
	menu_item menu_current;
	menu_item submenu_current;
	bool logined;
	bool more;
	std::string username;
	menu() {
		more = false;
		logined = false;
	}
};
