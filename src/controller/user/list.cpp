#include "list.h"

#include "../../model/user/list.h"

using namespace controller::user;

list::list(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"List","list")
{
	
}

void list::indexPage(std::string data)
{
    model::user::list c;
    prepare(c);
    display(c);
}
