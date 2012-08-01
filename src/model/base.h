#ifndef MODEL_BASE_H
#define MODEL_BASE_H

#include "../data/menu/item.h"

#include <cppcms/application.h>
#include <cppcms/url_mapper.h>
#include <cppcms/base_content.h>
#include <cppcms/base_view.h>
#include <cppcms/views_pool.h>
#include <cppcms/filters.h>

#include <list>

namespace model {

struct base : public cppcms::base_content {
    data::menu::item item;
    std::list< std::list<data::menu::item> > navigation;
};

}

#endif // MODEL_BASE_H

