#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include "../model/base.h"

#include <cppcms/application.h>

namespace controller {

class base : public cppcms::application
{
public:
    base(cppcms::service &srv, controller::base *parent = 0,
         const std::string &name = std::string(),
         const std::string &id = std::string());

    virtual void indexPage(std::string url) = 0;

    void prepare(model::base &c);
    void display(model::base &c);
};

}

#endif // CONTROLLER_BASE_H
