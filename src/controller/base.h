#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include "../model/base.h"

#include <cppcms/application.h>
#include <cppcms/service.h>

#include <booster/shared_ptr.h>

#include <list>

namespace controller {
class base : public cppcms::application
{
protected:
    base(cppcms::service &srv, base *parent = 0,
         const std::string &menuName = std::string(),
         const std::string &menuId = std::string(),
         const std::string &viewId = std::string());
    void attachItem(base *item);


    virtual void prepare(model::base &c);
    virtual void display(model::base &c, const std::string &tmpl = std::string(), const std::string &skin = "html");

    void error(int code, const std::string &message = std::string());

    void calculateMenu();

public:
    virtual void main(std::string url);
    virtual void indexPage(std::string url = std::string()) = 0;

    base * getParent() const;
    const std::string & getMenuName() const;
    const std::string & getMenuId() const;
    const std::string & getViewId() const;

private:
    void addChild(base *child);

    static std::vector< std::vector< std::string > > menus;
    base * m_parent;
    std::list<base*> m_children;
    std::string m_menuName;
    std::string m_menuId;
    std::string m_viewId;
};
}

#endif // CONTROLLER_BASE_H

