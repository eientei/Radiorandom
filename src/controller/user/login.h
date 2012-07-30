#ifndef CONTROLLER_USER_LOGIN_H
#define CONTROLLER_USER_LOGIN_H

#include "../base.h"

namespace controller {
namespace user {
class login : public controller::base
{
public:
    login(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace user
}

#endif // CONTROLLER_USER_LOGIN_H
