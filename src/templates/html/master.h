#ifndef MASTER_H
#define MASTER_H

#include <cppcms/view.h>
#include <cppcms/form.h>
#include <vector> 
#include <string> 

#include <PString/PString.h>


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
		bool logined;
		menu() {
			logined = false;
		}
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
    struct error :public master {
		int errorcode;
    };
    struct users :public master {
		std::string sort_username_dir;
		std::string sort_score_dir;
		std::string sort_access_dir;
		std::string sort_date_dir;
		users() {
			sort_username_dir = "desc";
			sort_score_dir = "desc";
			sort_access_dir = "desc";
			sort_date_dir = "desc";
		}
    };
	struct register_form : public cppcms::form {
		cppcms::widgets::submit submit;
		cppcms::widgets::text username;
		cppcms::widgets::email email;
		cppcms::widgets::email email_confirmation;
		cppcms::widgets::password password;
		cppcms::widgets::password password_confirmation;
		cppcms::widgets::checkbox tos;
		std::string username_message;
		std::string password_message;
		std::string password_confirmation_message;
		std::string email_message;
		std::string email_confirmation_message;
		register_form() {
			submit.value("Register");
			email_message = email_confirmation_message = "";
			password_message = password_confirmation_message = "";
			username_message = "";
			*this + username + email + email_confirmation + password + password_confirmation + tos + submit;
		}
		virtual bool validate() {
			bool result = true;
			if (PString(username.value().c_str()).length() < 5) {
				username_message = "Lesser then 5 characters";
				result = false;
			}
			if (PString(username.value().c_str()).length() > 32) {
				username_message = "Longer then 32 characters";
				result = false;
			}
			if (!email.validate()) {
				email.error_message("");
				email_message = "Wrong email";
				result = false;
			}
			if (email_confirmation.value() != email.value()) {
				email_confirmation_message = "Emails do not match";
				result = false;
			}
			if (PString(password.value().c_str()).length() < 6) {
				password_message = "Lesser then 6 characters";
				result = false;
			}
			if (PString(password.value().c_str()).length() > 32) {
				password_message = "Longer then 32 characters";
				result = false;
			}
			if (password_confirmation.value() != password.value()) {
				password_confirmation_message = "Password do not match";
				result = false;
			}
			if (!tos.value()) result = false;
			if (!result) return false;
			
			return true;
			/*
			if (!form::validate()) {
				email.error_message("");
				email_confirmation.error_message("");
				return false;
			}
			*/
		}
	};
    struct users_new :public master {
		std::string username_message;
		std::string password_message;
		std::string password_confirmation_message;
		std::string email_message;
		std::string email_confirmation_message;
		
		bool success;
		register_form registerform;
	};
    struct tos :public master {
	};
	struct login_form : public cppcms::form {
		cppcms::widgets::text username;
		cppcms::widgets::password password;
		cppcms::widgets::submit submit;
		login_form() {
			submit.value("Login");
			*this + username + password + submit;
		}
	};
    struct users_login :public master {
		std::string message;
		login_form loginform;
	};

}  

#endif
