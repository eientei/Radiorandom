#ifndef CONTROLLER_POST_INDEX_H
#define CONTROLLER_POST_INDEX_H

#include "../base.h"

namespace controller {
namespace post {
class index : public controller::base
{
public:
    index(cppcms::service &srv, controller::base *parent = 0);

    virtual void indexPage(std::string url);
};
} // namespace post
}

#endif // CONTROLLER_POST_INDEX_H
