#include "controller.hpp"

controller::generic::generic(cppcms::service & srv, std::string module_name)
    :
      cppcms::application(srv), m_menu_item(module_name)
{
    init_is_installed();
    init_error_codes();

    std::cout << "  [NEW]   " << m_menu_item << std::endl;
}

controller::generic::~generic() {
    std::cout << "  [DEL]   " << m_menu_item << std::endl;
}


// private

void controller::generic::init_is_installed() {
    m_lock_file = settings().find("cms.install_lock_file").get_value<std::string>();
    m_is_installed = util::fs::file_exists(m_lock_file);
}

void controller::generic::init_error_codes() {
    m_error_codes[404] = "Not Found";
    m_error_codes[403] = "Access Denied";
}

// protected

void controller::generic::please_install() {
    content::please_install c;
    prepare(c,"index");
    c.menu_item = "installer";
    display(c,"please_install");
}

void controller::generic::error(int code, std::string message) {
    content::error c;
    prepare(c,"error");
    c.code = code;
    if (message.empty()) message = m_error_codes[code];
    if (!message.empty()) {
        c.message = " - " + message;
    }
    display(c,"error");
}

void controller::generic::prepare(content::generic &c, std::string submenu_item) {
    c.is_installed = m_is_installed;
    c.menu_item = m_menu_item;
    c.submenu_item = submenu_item;

    c.menu_items["core"] = "Core";
    c.menu_items["user"] = "User";
    c.menu_items["post"] = "Post";
}

void controller::generic::display(content::generic &c, std::string tmpl, std::string skin) {
    render(skin,tmpl,c);
}

void controller::generic::do_dispatch(std::string url) {
    if (!dispatcher().dispatch(url)) {
        if (is_installed()) {
            error(404);
        } else {
            please_install();
        }
    }
}

// public

bool controller::generic::is_installed() {
    return m_is_installed;
}

std::string controller::generic::lock_file() {
    return m_lock_file;
}


void controller::generic::main(std::string url) {
    do_dispatch(url);;
}
