#ifndef MASTER_H
#define MASTER_H

#include <cppcms/view.h>
#include <vector> 
#include <string> 

struct menu_item {
	std::string name;
	std::string href;
};
typedef std::vector<menu_item> links_set;

namespace master  {  
    struct menu :public cppcms::base_content {
		links_set menu_links_left;
		links_set menu_links_right;
		menu_item menu_current;
	};
    struct master :public menu {
    };
    struct index :public master {
	};

}  

#endif
