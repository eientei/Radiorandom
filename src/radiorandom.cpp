#include "radiorandom.h"

#include "controller/index.h"

#include <cppcms/applications_pool.h>
#include <cppcms/service.h>

#include <iostream>

radiorandom::radiorandom(int argc, char **argv)
    : m_argc(argc), m_argv(argv)
{
}

void radiorandom::execute()
{
    try {
        cppcms::service srv(m_argc,m_argv);
        srv.applications_pool().mount(
                    cppcms::applications_factory<controller::index>());
        std::cout << "fired up" << std::endl;
        srv.run();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        // what else could we do? restart the app?
    }
}

