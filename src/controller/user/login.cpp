#include "login.h"

#include "../../model/user/login.h"

using namespace controller::user;

login::login(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Login","login")
{
	
}

void login::indexPage(std::string data)
{
    model::user::login c;
    prepare(c);
    display(c);
}

