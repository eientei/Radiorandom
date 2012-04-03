#include "controller.hpp"

// private

// protected

// public

controller::core::core(cppcms::service &srv) : generic(srv,"core") {
    mapper().root("/");
    mapper().assign("");
    mapper().assign("core","");

    if (!is_installed()) {
        attach(new controller::installer(srv), "installer", "installer{1}", "/installer((/.*)?)",1);
        return;
    }

    attach(new controller::post(srv), "post", "post{1}", "/post((/.*)?)",1);
    attach(new controller::user(srv), "user", "user{1}", "/user((/.*)?)",1);

    dispatcher().assign("/*",&controller::core::index,this);
}

void controller::core::index() {
    content::core::index c;
    prepare(c,"index");
    display(c,"core_index");
}
