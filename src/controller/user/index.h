#ifndef CONTROLLER_USER_INDEX_H
#define CONTROLLER_USER_INDEX_H

#include "../base.h"

namespace controller {
namespace user {
class index : public controller::base
{
public:
    index(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace user
}

#endif // CONTROLLER_USER_INDEX_H
