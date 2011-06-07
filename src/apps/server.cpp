#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/applications_pool.h>
#include <iostream>
#include <stdlib.h>

#include "master.h"


class radio_random : public cppcms::application {
	public:
		radio_random(cppcms::service &srv) : 
			cppcms::application(srv) 
		{
			dispatcher().assign("/",&radio_random::index,this,1);
		}
		void index(std::string url) {
			master::index c;
			menu_item item;

			item.name="[Index]";
			item.href="/";
			c.menu_current = item;
			c.menu_links_left.push_back(item);

			item.name="[Playlist]";
			item.href="/playlist";
			c.menu_links_left.push_back(item);
			
			item.name="[Users]";
			item.href="/users";
			c.menu_links_left.push_back(item);
			
			item.name="[Register]";
			item.href="/users/new";
			c.menu_links_right.push_back(item);
			
			render("radiorandom_index",c);
		}
};


int main(int argc, char **argv) {
//	printf("Server fired up\n");
	try {
		cppcms::service srv(argc,argv);
		srv.applications_pool().mount(cppcms::applications_factory<radio_random>());
		srv.run();
	} catch(std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}
}
