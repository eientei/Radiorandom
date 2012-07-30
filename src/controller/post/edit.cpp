#include "edit.h"

#include "../../model/post/edit.h"

using namespace controller::post;

edit::edit(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Edit","edit")
{
	
}

void edit::indexPage(std::string data)
{
    model::post::edit c;
    prepare(c);
    display(c);
}

