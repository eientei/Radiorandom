#include "error.h"

#include "../model/error.h"

using namespace controller;

error::error(cppcms::service &srv, controller::base *parent) 
    : controller::base(srv,parent,"Error","error")
{
	
}

void error::indexPage(std::string data)
{
    model::error c;
    prepare(c);
    display(c);
}

