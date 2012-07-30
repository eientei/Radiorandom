#include "index.h"

#include "../model/index.h"

using namespace controller;

index::index(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Index","index")
{
	
}

void index::indexPage(std::string data)
{
    model::index c;
    prepare(c);
    display(c);
}

