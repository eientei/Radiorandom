#include "root.h"

#include "user/root.h"
#include "post/root.h"

#include "../model/root.h"

using namespace controller;

root::root(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Root","root")
{
    new controller::user::root(srv,this);
    new controller::post::root(srv,this);

    std::list<base*> list;
    list.push_back(this);
    init(list);
}

void root::indexPage(std::string data)
{
    model::root c;
    prepare(c);
    display(c);
}

