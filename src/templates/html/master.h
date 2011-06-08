#ifndef MASTER_H
#define MASTER_H

#include <cppcms/view.h>
#include <cppcms/form.h>
#include <vector> 
#include <string> 

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

namespace master  {  
    struct menu :public cppcms::base_content {
		links_set menu_links_left;
		links_set menu_links_right;
		menu_item menu_current;
	};
    struct master :public menu {
    };
    struct index :public master {
		size_t files;
		size_t filessize;
		std::string format_filessize(size_t size) {
			char buf[1024];
			float fsize = size;
			std::string suffix("B");
			if (size / 1024 > 0) {
				suffix = "KB";
				size /= 1024;
				fsize /= 1024;
			}
			if (size / 1024 > 0) {
				suffix = "MB";
				size /= 1024;
				fsize /= 1024;
			}
			if (size / 1024 > 0) {
				suffix = "GB";
				size /= 1024;
				fsize /= 1024;
			}
			if (size / 1024 > 0) {
				suffix = "TB";
				size /= 1024;
				fsize /= 1024;
			}
			snprintf(buf,1024,"%.2f",fsize);
			return buf + std::string(" ") + suffix;
		}
	};
	struct setup_form : public cppcms::form {
		cppcms::widgets::submit submit;
		setup_form() {
			submit.value("Setup");
			*this + submit;
		}
	};
    struct setup :public master {
		bool already_setted_up;
		bool submut_res;
		setup_form setupform;
    };

}  

#endif
