#include "index.h"

#include "../model/index.h"

#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

using namespace controller;

index::index(cppcms::service &srv, base *parent)
    : controller::base(srv,parent,"Index","","index")
{
    dispatcher().assign("/*",&index::indexPage,this);
    mapper().assign("");
}

void index::indexPage()
{
    model::index c;
    prepare(c);
    display(c);
}
