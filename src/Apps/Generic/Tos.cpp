#include <Apps/Server.h>

void controller::tos() {
	model::tos c;
	prepare(c,menu_item("[TOS]","/tos"));
	render("html_tos",c);
}
