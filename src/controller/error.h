#ifndef CONTROLLER_ERROR_H
#define CONTROLLER_ERROR_H

#include "base.h"

namespace controller {

class error : public controller::base
{
public:
    error(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};

}

#endif // CONTROLLER_ERROR_H
