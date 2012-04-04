#include "controller.hpp"

// private

// protected

void controller::user::prepare(content::generic &c, std::string submenu_item) {
    controller::generic::prepare(c,submenu_item);

    c.submenu_items["list"]   = "List";
    c.submenu_items["signup"] = "Signup";
}

// public

controller::user::user(cppcms::service &srv) : generic(srv,"user") {
    dispatcher().assign("/*",&controller::user::index,this);
    mapper().assign("");

    dispatcher().assign("/list/*",&controller::user::list,this);
    mapper().assign("list","/list");

    dispatcher().assign("/signup/*",&controller::user::signup,this);
    mapper().assign("signup","/signup");
}

void controller::user::index() {
    content::user::index c;
    prepare(c,"index");
    display(c,"user_index");
}

void controller::user::list() {
    content::user::list c;
    prepare(c,"list");
    display(c,"user_list");
}

void controller::user::signup() {
    content::user::signup c;
    prepare(c,"signup");
    display(c,"user_signup");
}
