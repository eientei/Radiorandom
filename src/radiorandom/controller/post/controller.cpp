#include "controller.hpp"

controller::post::post(cppcms::service &srv) : generic(srv,"post") {
    dispatcher().assign("/*",&controller::post::index,this);
    mapper().assign("");
}

void controller::post::index() {
    content::post::index c;
    prepare(c,"index");
    display(c,"post_index");
}
