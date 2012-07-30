#include "index.h"

#include "../../model/user/index.h"

using namespace controller::user;

index::index(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Index","index")
{
	
}

void index::indexPage(std::string data)
{
    model::user::index c;
    prepare(c);
    display(c);
}

