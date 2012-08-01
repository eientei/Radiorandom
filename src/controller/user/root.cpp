#include "root.h"

#include "list.h"
#include "login.h"
#include "logout.h"
#include "signup.h"

#include "../../model/user/root.h"

#include <cppcms/url_dispatcher.h>

using namespace controller::user;

root::root(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"User","user")
{
    new controller::user::list(srv,this);
    new controller::user::login(srv,this);
    new controller::user::logout(srv,this);
    new controller::user::signup(srv,this);

    //dispatcher().assign("/*",&controller::user::root::indexPage,this,1);
}

void root::indexPage(std::string data)
{
    model::user::root c;
    prepare(c);
    display(c);
}

