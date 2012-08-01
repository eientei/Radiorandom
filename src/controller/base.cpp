#include "base.h"

#include "../model/base.h"
#include "../model/error.h"

#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>


using namespace controller;

base::base(cppcms::service &srv, controller::base *parent,
           const std::string &name, const std::string &id)
    : cppcms::application(srv), m_parent(parent)
{
    if (parent != 0) {
        parent->m_children.push_back(this);
        m_item = data::menu::item(name,id,parent->getItem());
    } else {
        m_item = data::menu::item(name,id);
    }
    dispatcher().assign("/*",&base::indexPage,this,1);
    mapper().assign("");
}

void base::main(std::string url)
{
    if (!dispatcher().dispatch(url)) {
        error(404);
    }
}

void base::prepare(model::base &c)
{
    c.item = getItem();
    c.navigation = getNavigation();
}

void base::display(model::base &c, const std::string &tmpl, const std::string &skin)
{
    if (tmpl.empty()) {
        render(skin,getItem().id,c);
    } else {
        render(skin,tmpl,c);
    }
}

void base::error(int code, const std::string &msg)
{
    model::error c;
    prepare(c);
    c.code = code;
    if (msg.empty()) {
        c.message = response().status_to_string(code);
    } else {
        c.message = msg;
    }
    response().status(code);
    display(c,"error");
}


void base::init(const std::list<base*> &apps)
{
    std::list<base*>::const_iterator it,end,subit,subend;
    base *p;

    end = apps.end();

    for (it=apps.begin(); it != end; it++) {
        p = *it;
        while (p != 0) {
            std::list<data::menu::item> dim;
            subend = p->getChildren().end();
            for (subit = p->getChildren().begin(); subit != subend; subit++) {
                dim.push_back((*subit)->getItem());
            }
            (*it)->m_navigation.push_front(dim);
            p = p->getParent();
        }

        if ((*it)->getParent() != 0) {
            (*it)->getParent()->attach(*it);
            (*it)->getParent()->dispatcher().mount("/" + (*it)->getItem().orig_id + "((/.*)?)", *(*it),1);
            mapper().mount((*it)->getItem().id,(*it)->getItem().path + "{1}",*(*it));

            std::cout << "Mapping: " << (*it)->getItem().id << " -> " << (*it)->getItem().path << std::endl;
        }
        if (!(*it)->getChildren().empty()) {
            init((*it)->getChildren());
        }
    }
}

const data::menu::item &base::getItem()
{
    return m_item;
}

const std::list<base*> & base::getChildren()
{
    return m_children;
}

const std::list< std::list<data::menu::item> > &base::getNavigation()
{
    return m_navigation;
}

base *base::getParent()
{
    return m_parent;
}

