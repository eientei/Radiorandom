#ifndef CONTROLLER_ROOT_H
#define CONTROLLER_ROOT_H

#include "base.h"

namespace controller {

class root : public controller::base
{
public:
    root(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};

}

#endif // CONTROLLER_ROOT_H
