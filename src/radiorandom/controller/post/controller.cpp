#include "controller.hpp"

// private

// protected


void controller::post::prepare(content::generic &c, std::string submenu_item) {
    controller::generic::prepare(c,submenu_item);

    c.submenu_items["list"]   = "List";
    c.submenu_items["upload"] = "Upload";
}


// public

controller::post::post(cppcms::service &srv) : generic(srv,"post") {
    dispatcher().assign("/*",&controller::post::index,this);
    mapper().assign("");

    dispatcher().assign("/list/*",&controller::post::list,this);
    mapper().assign("list","/list");

    dispatcher().assign("/upload/*",&controller::post::upload,this);
    mapper().assign("upload","/upload");
}

void controller::post::index() {
    content::post::index c;
    prepare(c,"index");
    display(c,"post_index");
}

void controller::post::list() {
    content::post::list c;
    prepare(c,"list");
    display(c,"post_list");
}

void controller::post::upload() {
    content::post::upload c;
    prepare(c,"upload");
    display(c,"post_upload");
}
