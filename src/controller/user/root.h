#ifndef CONTROLLER_USER_ROOT_H
#define CONTROLLER_USER_ROOT_H

#include "../base.h"

namespace controller {
namespace user {
class root : public controller::base
{
public:
    root(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace user
}

#endif // CONTROLLER_USER_ROOT_H
