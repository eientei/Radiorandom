#include "add.h"

#include "../../model/post/add.h"

using namespace controller::post;

add::add(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Add","add")
{
	
}

void add::indexPage(std::string data)
{
    model::post::add c;
    prepare(c);
    display(c);
}

