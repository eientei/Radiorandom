#ifndef CONTROLLER_POST_ADD_H
#define CONTROLLER_POST_ADD_H

#include "../base.h"

namespace controller {
namespace post {
class add : public controller::base
{
public:
    add(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace post
}

#endif // CONTROLLER_POST_ADD_H
