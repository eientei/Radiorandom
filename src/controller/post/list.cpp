#include "list.h"

#include "../../model/post/list.h"

using namespace controller::post;

list::list(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"List","list")
{
	
}

void list::indexPage(std::string data)
{
    model::post::list c;
    prepare(c);
    display(c);
}

