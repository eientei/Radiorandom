#ifndef CONTROLLER_POST_LIST_H
#define CONTROLLER_POST_LIST_H

#include "../base.h"

namespace controller {
namespace post {
class list : public controller::base
{
public:
    list(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace post
}

#endif // CONTROLLER_POST_LIST_H
