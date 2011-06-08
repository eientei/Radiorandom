#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
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

class radio_random : public cppcms::application {
	private:
		void set_menu(master::menu &c) {
			c.menu_links_left.push_back(menu_item("[Index]","/"));
			c.menu_links_left.push_back(menu_item("[Playlist]","/playlist"));
			c.menu_links_left.push_back(menu_item("[Users]","/users"));
			c.menu_links_right.push_back(menu_item("[Register]","/users/new"));
			
		}
	public:
		radio_random(cppcms::service &srv) : 
			cppcms::application(srv) 
		{
			dispatcher().assign("/",&radio_random::index,this);
			dispatcher().assign("/setup",&radio_random::setup,this);
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
			dispatcher().dispatch(url);
		}
};


int main(int argc, char **argv) {
	printf("Server fired up\n");
	try {
		cppcms::service srv(argc,argv);
		srv.applications_pool().mount(cppcms::applications_factory<radio_random>());
		srv.run();
	} catch(std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}
}
