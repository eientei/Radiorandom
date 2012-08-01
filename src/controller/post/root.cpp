#include "root.h"

#include "add.h"
#include "edit.h"
#include "list.h"

#include "../../model/post/root.h"

using namespace controller::post;

root::root(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Post","post")
{
    new controller::post::add(srv,this);
    new controller::post::edit(srv,this);
    new controller::post::list(srv,this);
}

void root::indexPage(std::string data)
{
    model::post::root c;
    prepare(c);
    display(c);
}
