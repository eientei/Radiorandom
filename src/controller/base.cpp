#include "base.h"

#include "../model/error.h"

#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <cppcms/http_response.h>

using namespace controller;


base::base(cppcms::service &srv, base *parent,
           const std::string &menuName,
           const std::string &menuId,
           const std::string &viewId)
    : cppcms::application(srv),
      m_parent(parent),
      m_menuName(menuName),
      m_menuId(menuId),
      m_viewId(viewId)
{
    if (parent != 0) {
        parent->addChild(this);
    }
    dispatcher().assign("/*",&base::indexPage,this,1);
    //mapper().assign("");
}

void base::attachItem(base *item)
{
    attach(item,
           item->getMenuName(),"/" + item->getMenuId() + "{1}",
           "/" + item->getMenuId() + "((/.*)?)",1);
}

void base::main(std::string url)
{
    if (!dispatcher().dispatch(url)) {
        error(404);
    }
}


void base::prepare(model::base &c)
{

}

void base::display(model::base &c, const std::string &tmpl, const std::string &skin)
{
    if (tmpl.empty()) {
        render(skin,getViewId(),c);
    } else {
        render(skin,tmpl,c);
    }

}

void base::error(int code, const std::string &message)
{
    model::error c;

    prepare(c);

    c.code = code;

    if (message.empty()) {
        c.message = response().status_to_string(code);
    } else {
        c.message = message;
    }

    response().status(code);

    display(c,"error");
}

void base::calculateMenu()
{

}

base* base::getParent() const
{
    return m_parent;
}

const std::string &base::getMenuName() const
{
    return m_menuName;
}

const std::string &base::getMenuId() const
{
    return m_menuId;
}

const std::string &base::getViewId() const
{
    return m_viewId;
}

void base::addChild(base *child)
{
    m_children.push_back(child);
}
