#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include "../model/base.h"

#include "../data/menu/item.h"

#include <cppcms/service.h>
#include <cppcms/application.h>

#include <string>
#include <list>

namespace controller {

class base : public cppcms::application
{
public:
    base(cppcms::service &srv, controller::base *parent = 0,
         const std::string &name = std::string(),
         const std::string &id   = std::string());

    virtual void indexPage(std::string url) = 0;
    virtual void main(std::string url);

protected:
    void prepare(model::base &c);
    void display(model::base &c, const std::string &tmpl = std::string(), const std::string &skin = "html");
    void error(int code, const std::string &msg = std::string());
    void init(const std::list<base*> &apps);

    const data::menu::item & getItem();
    const std::list<base*> & getChildren();
    const std::list< std::list<data::menu::item> > & getNavigation();
    base * getParent();


private:
    data::menu::item m_item;
    std::list< std::list<data::menu::item> > m_navigation;
    std::list< base* > m_children;
    base * m_parent;
};

}

#endif // CONTROLLER_BASE_H
