#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include "../model/base.h"

#include "../data/menu/item.h"

#include <cppcms/application.h>

#include <list>

namespace controller {

class base : public cppcms::application
{
public:
    base(cppcms::service &srv, controller::base *parent = 0,
         const std::string &name = std::string(),
         const std::string &id = std::string());

    virtual void indexPage(std::string url) = 0;

    virtual void main(std::string url);

    base *getParent();
    const std::list<base*> & getChildren();

protected:
    void prepare(model::base &c);
    void display(model::base &c, const std::string &tmpl = std::string(), const std::string &skin = std::string());
    void error(int code, const std::string &message = std::string());
    void updateMenu();
    std::string getViewId();
    const std::string & getName();
    const std::string & getId();

private:
    void addChild(base *child);

    data::menu::item m_item;
    std::list<base*> m_children;

    base *m_parent;

};

}

#endif // CONTROLLER_BASE_H
