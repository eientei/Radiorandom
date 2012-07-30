#include "index.h"

#include "../../model/post/index.h"

using namespace controller::post;

index::index(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Index","index")
{
	
}

void index::indexPage(std::string data)
{
    model::post::index c;
    prepare(c);
    display(c);
}

