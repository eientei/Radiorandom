#ifndef CONTROLLER_INDEX_H
#define CONTROLLER_INDEX_H

#include "base.h"

namespace controller {

class index : public controller::base
{
public:
    index(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};

}

#endif // CONTROLLER_INDEX_H
