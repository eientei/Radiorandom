struct menu :public cppcms::base_content {
	links_set menu_links_left;
	links_set menu_links_right;
	menu_item menu_current;
	bool logined;
	menu() {
		logined = false;
	}
};
