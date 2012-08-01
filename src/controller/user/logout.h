#ifndef CONTROLLER_USER_LOGOUT_H
#define CONTROLLER_USER_LOGOUT_H

#include "../base.h"

namespace controller {
namespace user {
class logout : public controller::base
{
public:
    logout(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace user
}

#endif // CONTROLLER_USER_LOGOUT_H
