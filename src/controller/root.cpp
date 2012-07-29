#include "root.h"

#include "index.h"

using namespace controller;

root::root(cppcms::service &srv)
    : controller::base(srv,0)
{
    attachItem(new controller::index(srv,this));
}
