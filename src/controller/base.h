#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include <cppcms/application.h>

namespace controller {

class base : public cppcms::application
{
public:
    base(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url) = 0;
};

}

#endif // CONTROLLER_BASE_H
