#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_cookie.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/applications_pool.h>
#include <cppcms/json.h>

#include <cppdb/frontend.h>

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "master.h"
#include <gcrypt.h>

char *sha1hash(const char *buf) {
	int input_len = strlen(buf);
	int hash_len = gcry_md_get_algo_dlen(GCRY_MD_SHA1);
	unsigned char *binary_hash = new unsigned char[hash_len];
	char *textual_hash = new char[hash_len * 2 + 1];
	char *p = textual_hash;
	gcry_md_hash_buffer(GCRY_MD_SHA1,binary_hash,buf,input_len);
	for (int i=0; i < hash_len; i++, p+=2) {
		snprintf(p,3,"%02x",binary_hash[i]);
	}
	delete[] binary_hash;	
	return textual_hash;
}

bool valid_user(std::string username, std::string password_hash) {
	cppdb::session users_sql("sqlite3:db=db/users.db");
	cppdb::result users = users_sql << "select count(*) from users where username = ? and password_hash = ?" << username << password_hash;
	users.next();
	return users.get<int>(0) == 1;
}

class radio_random : public cppcms::application {
	private:
		void set_menu(master::menu &c, bool login = false) {
			std::string username = request().cookie_by_name("username").value();
			std::string password_hash = request().cookie_by_name("password_hash").value();
			c.menu_links_left.push_back(menu_item("[Index]","/"));
			c.menu_links_left.push_back(menu_item("[Playlist]","/playlist"));
			c.menu_links_left.push_back(menu_item("[Users]","/users"));
			
			if (valid_user(username,password_hash) || login) {
				c.menu_links_right.push_back(menu_item("[Home]","/users/profile"));
				c.menu_links_right.push_back(menu_item("[Logout]","/users/logout"));
			} else {
				c.menu_links_right.push_back(menu_item("[Login]","/users/login"));
				c.menu_links_right.push_back(menu_item("[Register]","/users/new"));
			}
			c.menu_links_right.push_back(menu_item("[TOS]","/tos"));
			
		}
	public:
		radio_random(cppcms::service &srv) : 
			cppcms::application(srv) 
		{
			dispatcher().assign("/",&radio_random::index,this);
			dispatcher().assign("/setup",&radio_random::setup,this);
			dispatcher().assign("/tos",&radio_random::tos,this);
			dispatcher().assign("/users($|\\?.*)",&radio_random::users,this);
			dispatcher().assign("/users/new",&radio_random::users_new,this);
			dispatcher().assign("/users/logout",&radio_random::users_logout,this);
			dispatcher().assign("/users/login",&radio_random::users_login,this);
		}
		void users_login() {
			master::users_login c;
			set_menu(c);
			c.menu_current = menu_item("[Login]","/users/login");
			
			if(request().request_method()=="POST") {
				c.loginform.load(context());
				std::string username = c.loginform.username.value();
				std::string password = c.loginform.password.value();\
				char *password_hash = sha1hash(password.c_str());
				if (valid_user(username,password_hash)) {
					response().set_redirect_header("/");
					response().set_cookie(cppcms::http::cookie::cookie("username",username,60*60*24*31*12,"/","radiorandom.neverb.net"));
					response().set_cookie(cppcms::http::cookie::cookie("password_hash",password_hash,60*60*24*31*12,"/","radiorandom.neverb.net"));
				} else {
					c.message = "Wrong login/password.";
				}
				delete[] password_hash;
			}
			
			render("radiorandom_users_login",c);
		}
		void users_logout() {
			response().set_redirect_header("/");
			response().set_cookie(cppcms::http::cookie::cookie("username","",0,"/","radiorandom.neverb.net"));
			response().set_cookie(cppcms::http::cookie::cookie("password_hash","",0,"/","radiorandom.neverb.net"));
		}
		void tos() {
			master::tos c;
			set_menu(c);
			c.menu_current = menu_item("[TOS]","/tos");
			
			render("radiorandom_tos",c);
		}
		void users_new() {
			master::users_new c;
			c.success = false;
			c.menu_current = menu_item("[Register]","/users/new");
			
			if(request().request_method()=="POST") {
				c.registerform.load(context());
				if (c.registerform.validate()) {
					
					cppdb::session users_sql("sqlite3:db=db/users.db");
					cppdb::result users = users_sql << "select count(*) from users where username = ?" << c.registerform.username.value();
					users.next();
					if (users.get<int>(0) == 0) {
						char *hash = sha1hash(c.registerform.password.value().c_str());
						users_sql << "insert into users values (?,?,0,0,datetime('now'))" << c.registerform.username.value() << hash << cppdb::exec;
						
						c.success = true;
						
						response().set_cookie(cppcms::http::cookie::cookie("username",c.registerform.username.value(),60*60*24*31*12,"/","radiorandom.neverb.net"));
						response().set_cookie(cppcms::http::cookie::cookie("password_hash",hash,60*60*24*31*12,"/","radiorandom.neverb.net"));
						
						set_menu(c,true);

						delete[] hash;
						
												
						render("radiorandom_users_new",c);
						c.registerform.clear();
						
						return;
					}
						
					c.username_message = "This username already exists";

				}
				c.username_message += c.registerform.username_message;
				c.email_message = c.registerform.email_message;
				c.email_confirmation_message = c.registerform.email_confirmation_message;
				c.password_message = c.registerform.password_message;
				c.password_confirmation_message = c.registerform.password_confirmation_message;
			}
			set_menu(c);
			render("radiorandom_users_new",c);
		}
		void users() {
			master::users c;
			set_menu(c);
			
			std::multimap<std::string,std::string> getreq = request().get();
			if (getreq.find("direction")->second == "asc") {
				if (getreq.find("sortby")->second == "username") {
					c.sort_username_dir = "desc";
				}
				if (getreq.find("sortby")->second == "score") {
					c.sort_score_dir = "desc";
				}
				if (getreq.find("sortby")->second == "access") {
					c.sort_access_dir = "desc";
				}
				if (getreq.find("sortby")->second == "date") {
					c.sort_date_dir = "desc";
				}
			} else {
				if (getreq.find("sortby")->second == "username") {
					c.sort_username_dir = "asc";
				}
				if (getreq.find("sortby")->second == "score") {
					c.sort_score_dir = "asc";
				}
				if (getreq.find("sortby")->second == "access") {
					c.sort_access_dir = "asc";
				}
				if (getreq.find("sortby")->second == "date") {
					c.sort_date_dir = "asc";
				}
			}
			
			c.menu_current = menu_item("[Users]","/users");
			
			render("radiorandom_users",c);
		}
		void setup() {
			master::setup c;
			set_menu(c);
			
			c.already_setted_up = false;
			c.submut_res = false;
			
			std::string setuplock = settings().get<std::string>("setup.lockfile");
			
			struct stat filestatus;
			stat(setuplock.c_str(), &filestatus);
			if (S_ISREG(filestatus.st_mode)) {
				c.already_setted_up = true;
				render("radiorandom_setup",c);
				return;
			}
			if(request().request_method()=="POST") {
				c.setupform.load(context());
				c.submut_res = c.setupform.submit.value();
				c.setupform.clear();
				FILE *fp = fopen(setuplock.c_str(),"w");
				fclose(fp);
				
				try {
					std::string users_schema = settings().get<std::string>("db-schema.users");
					std::string files_schema = settings().get<std::string>("db-schema.files");
					cppdb::session users_sql("sqlite3:db=db/users.db");
					cppdb::session files_sql("sqlite3:db=db/files.db");
					users_sql << "drop table users" << cppdb::exec;
					files_sql << "drop table files" << cppdb::exec;
					users_sql << users_schema << cppdb::exec;
					files_sql << files_schema << cppdb::exec;
					
				} catch (std::exception const &e) {
					std::cerr << e.what() << std::endl;
				}
			}
			render("radiorandom_setup",c);
		}
		void index() {
			master::index c;
			
			set_menu(c);

			c.menu_current = menu_item("[Index]","/");
			
			c.files = 0;
			c.filessize = 0;
			
			try {
				cppdb::session sql("sqlite3:db=db/files.db");
			} catch (std::exception const &e) {
				std::cerr << e.what() << std::endl;
			}
			
			render("radiorandom_index",c);
		}
		void main(std::string url) {
			if (!dispatcher().dispatch(url)) {
				master::error c;
				
				set_menu(c);
				
				c.errorcode = 404;
				render("radiorandom_error",c);
			}
		}
};


int main(int argc, char **argv) {
	printf("Server fired up\n");
	pio_init();
	try {
		cppcms::service srv(argc,argv);
		srv.applications_pool().mount(cppcms::applications_factory<radio_random>());
		srv.run();
	} catch(std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}
}
