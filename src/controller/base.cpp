#include "base.h"

using namespace controller;

base::base(cppcms::service &srv, controller::base *parent,
           const std::string &name,
           const std::string &id)
    : cppcms::application(srv)
{

}

void base::prepare(model::base &c)
{
}

void base::display(model::base &c)
{
}
