#ifndef CONTROLLER_SUPERCLASS_APPLICATION_HPP
#define CONTROLLER_SUPERCLASS_APPLICATION_HPP


#include <cppcms/application.h>

#include "superclass.hpp"


namespace controller {
    class superclass_application : public cppcms::application {
            superclass_application(cppcms::service & srv)
                : cppcms::application(srv)
            {

            }
    };
}

#endif // CONTROLLER_SUPERCLASS_APPLICATION_HPP
