#include "base.h"

#include "../model/base.h"
#include "../model/error.h"

#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>

using namespace controller;

base::base(cppcms::service &srv, controller::base *parent,
           const std::string &name,
           const std::string &id)
    : cppcms::application(srv), m_parent(parent), m_item(name,id)
{

}

void base::main(std::string url)
{
    if (!dispatcher().dispatch(url)) {
        error(404);
    }
}

base *base::getParent()
{
    return m_parent;
}

const std::list<base*> & base::getChildren()
{
    return m_children;
}

void base::prepare(model::base &c)
{
    // do preparations
}

void base::display(model::base &c,
                   const std::string &tmpl,
                   const std::string &skin)
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
    if(message.empty()) {
        c.message = response().status_to_string(code);
    } else {
        c.message = message;
    }

    response().status(code);

    display(c);
}

void base::updateMenu()
{
}

std::string base::getViewId()
{
    std::string result = getId();

    base *p = getParent();
    while (p != 0) {
        result = p->getId() + "_" + result;
        p = p->getParent();
    }

    return result;
}

const std::string &base::getName()
{
    return m_item.name;
}

const std::string &base::getId()
{
    return m_item.id;
}

void base::addChild(base *child)
{
    m_children.push_back(child);
}
