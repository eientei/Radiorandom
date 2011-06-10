#include <Apps/Server.h>

void controller::posts() {
	model::posts c;
	prepare(c,menu_item("[Posts]","/posts"));
	
}
