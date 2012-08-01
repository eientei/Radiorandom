#include "logout.h"

#include "../../model/user/logout.h"

using namespace controller::user;

logout::logout(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Logout","logout")
{
	
}

void logout::indexPage(std::string data)
{
    model::user::logout c;
    prepare(c);
    display(c);
}

