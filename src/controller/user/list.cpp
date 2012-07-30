#include "list.h"

#include "../model/user/list.h"

using namespace controller::user;

list::list(cppcms::service &srv, controller::base *parent)
    : controller::base(srv,parent,"List","list","user_list")
{
}

void list::indexPage(std::string url)
{
    model::user::list c;
    prepare(c);
    display(c);
}
