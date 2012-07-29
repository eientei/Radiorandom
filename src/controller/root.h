#ifndef CONTROLLER_ROOT_H
#define CONTROLLER_ROOT_H

#include "base.h"

namespace controller {
class root : public controller::base
{
public:
    root(cppcms::service &srv);
};
}
#endif // CONTROLLER_ROOT_H
