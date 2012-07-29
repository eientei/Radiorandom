#ifndef MODEL_BASE_H
#define MODEL_BASE_H

#include <cppcms/base_content.h>
#include <cppcms/base_view.h>
#include <cppcms/views_pool.h>

#include <string>

namespace model {
struct base : public cppcms::base_content {

};

/*
struct error : public model::base {
    int code;
    std::string message;
};
*/
}

#endif // MODEL_BASE_H
