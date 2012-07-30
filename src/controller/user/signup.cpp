#include "signup.h"

#include "../../model/user/signup.h"

using namespace controller::user;

signup::signup(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Signup","signup")
{
	
}

void signup::indexPage(std::string data)
{
    model::user::signup c;
    prepare(c);
    display(c);
}

