#include "index.h"

#include "user/index.h"

#include "../model/index.h"


using namespace controller;

index::index(cppcms::service &srv, base *parent)
    : controller::base(srv,0,"Index","","index")
{
    attachItem(new controller::user::index(srv,this));
}

void index::indexPage(std::string data)
{
    model::index c;
    prepare(c);
    display(c);
}
