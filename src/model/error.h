#ifndef MODEL_ERROR_H
#define MODEL_ERROR_H

#include "base.h"

namespace model {

struct error : public base {
    int code;
    std::string message;
};

}

#endif // MODEL_ERROR_H

