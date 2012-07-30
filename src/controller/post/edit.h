#ifndef CONTROLLER_POST_EDIT_H
#define CONTROLLER_POST_EDIT_H

#include "../base.h"

namespace controller {
namespace post {
class edit : public controller::base
{
public:
    edit(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace post
}

#endif // CONTROLLER_POST_EDIT_H
