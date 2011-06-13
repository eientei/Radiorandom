#include <radiorandom/helpers/navigation/navigation.h>

/// @file

void helpers::navigation::gen_menu(models::master::menu &c,data::content::menu_item current, bool login, data::content::menu_item submenu_current) {
	c.menu_current = current;
	if (c.setted_up == false) {
		c.menu_right.push_back(data::content::menu_item("[Setup]","/setup"));
		return;
	}
	c.menu_left.push_back(data::content::menu_item("[Index]","/"));
	c.menu_left.push_back(data::content::menu_item("[Posts]","/posts"));
	c.menu_left.push_back(data::content::menu_item("[Users]","/users"));
	if ((c.user_authed == true) || login) {
		c.menu_right.push_back(data::content::menu_item("[Profile]","/users/profile"));
		c.menu_right.push_back(data::content::menu_item("[Logout]","/users/logout"));
	} else {
		c.menu_right.push_back(data::content::menu_item("[Register]","/users/new"));
		c.menu_right.push_back(data::content::menu_item("[Login]","/users/login"));
	}
	c.menu_right.push_back(data::content::menu_item("[TOS]","/tos"));
	if (current.name == "[Posts]") {
		c.is_submenu = true;
		c.submenu_current = submenu_current;
		c.submenu_left.push_back(data::content::menu_item("[Index]","/posts"));
		c.submenu_left.push_back(data::content::menu_item("[Upload]","/posts/new"));
		c.submenu_left.push_back(data::content::menu_item("[Search]","/posts/search"));
	}
	if (current.name == "[Users]") {
		char buf[1024];
		snprintf(buf,1024,"%d",c.user_id);
		c.is_submenu = true;
		c.submenu_current = submenu_current;
		c.submenu_left.push_back(data::content::menu_item("[Index]","/users"));
		if (c.user_authed) {
			c.submenu_left.push_back(data::content::menu_item("[My Profile]","/users/" + std::string(buf)));
		}
		c.submenu_left.push_back(data::content::menu_item("[Search]","/users/search"));
	}
}


std::string helpers::navigation::navgen_helper(int begin, int end, int page, int pagesize, std::string prefix, std::string infix, int pn) {
	std::string result = "";
	std::string c_class,href;
	char buf[1024];
	
	for (int i=begin; i < end; i+=pagesize) {
		snprintf(buf,1024,"%d",pn);
		if (pn == page) {
			c_class="current";
			href="";
		} else {
			c_class = "rest";
			href = " href=\"" + prefix + infix + "&amp;page=" + buf + "\"";
		}
		result += "<a class=\"" + c_class + "\"" + href + ">" + std::string(buf) + "</a>";
		pn++;
	}
	return result;
}


std::string helpers::navigation::generator(int page, int total, int pagesize, std::string prefix, std::string infix) {
	std::string result;
	std::string href;
	int total_pages = total / pagesize;
	if (total % pagesize) total_pages += 1;
	char buf[1024];
	if (page == 1) {
		result += "<a class=\"prev\">&lt;&lt;</a>";
	} else {
		snprintf(buf,1024,"%d",page - 1);
		result += "<a class=\"prev-active\" href=\"" + prefix + infix + "&amp;page=" + std::string(buf) + "\">&lt;&lt;</a>";
	}
	if (total_pages < 8) {
		result += helpers::navigation::navgen_helper(0,total,page,pagesize,prefix,infix);
	} else {
		if (page > 5) {
			result += "<a class=\"rest\" href=\"" + prefix + infix + "&amp;page=1\">1</a>";
			result += "...";
		}

		if (page < 6) {
			result += helpers::navigation::navgen_helper(0,(5+(page>=5&&2)+(page>5)+((page>=3) && abs(3-page)))*pagesize,page,pagesize,prefix,infix);
		}

		
		if ((page >= 6) && (((total_pages - page) >= 5))) {
			result += helpers::navigation::navgen_helper((page-2)*pagesize,(page+3)*pagesize,page,pagesize,prefix, infix,(page-2));
		}
		
		if ((total_pages - page) < 3) {
			result += helpers::navigation::navgen_helper(total-(5)*pagesize,total,page,pagesize,prefix, infix,(total_pages - 4));
		} else if ((total_pages - page) < 4) {
			result += helpers::navigation::navgen_helper(total-(6)*pagesize,total,page,pagesize,prefix, infix,(total_pages - 5));
		} else if ((total_pages - page) < 5) {
			result += helpers::navigation::navgen_helper(total-(7)*pagesize,total,page,pagesize,prefix, infix,(total_pages - 6));
		}


		if ((total_pages - page) > 4) {
			snprintf(buf,1024,"%d",total_pages);
			result += "...";
			result += "<a class=\"rest\" href=\"" + prefix + infix + "&amp;page=" + buf + "\">" + buf + "</a>";
		}
	}
	if (page == total_pages) {
		result += "<a class=\"next\">&gt;&gt;</a>";
	} else {
		snprintf(buf,1024,"%d",page+1);
		result += "<a class=\"next-active\" href=\"" + prefix + infix + "&amp;page=" + std::string(buf) + "\">&gt;&gt;</a>";
	}
	return result;
}
