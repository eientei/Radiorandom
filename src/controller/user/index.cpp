#include "index.h"

#include "list.h"

#include "../model/user/index.h"

using namespace controller::user;

index::index(cppcms::service &srv, controller::base *parent)
    : controller::base(srv,parent,"Users","user","user_index")
{
    attachItem(new controller::user::list(srv,this));
}

void index::indexPage(std::string data)
{
    model::user::index c;
    prepare(c);
    display(c);
}
