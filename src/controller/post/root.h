#ifndef CONTROLLER_POST_ROOT_H
#define CONTROLLER_POST_ROOT_H

#include "../base.h"

namespace controller {
namespace post {
class root : public controller::base
{
public:
    root(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace post
}

#endif // CONTROLLER_POST_ROOT_H
