#include "controller.hpp"

controller::user::user(cppcms::service &srv) : generic(srv,"user") {
    dispatcher().assign("/*",&controller::user::index,this);
    mapper().assign("");
}

void controller::user::index() {
    content::user::index c;
    prepare(c,"index");
    display(c,"user_index");
}
