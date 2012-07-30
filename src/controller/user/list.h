#ifndef CONTROLLER_USER_LIST_H
#define CONTROLLER_USER_LIST_H

#include "../base.h"

namespace controller {
namespace user {
class list : public controller::base
{
public:
    list(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace user
}

#endif // CONTROLLER_USER_LIST_H
