#ifndef CONTROLLER_USER_SIGNUP_H
#define CONTROLLER_USER_SIGNUP_H

#include "../base.h"

namespace controller {
namespace user {
class signup : public controller::base
{
public:
    signup(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace user
}

#endif // CONTROLLER_USER_SIGNUP_H
