#ifndef MODEL_ERROR_HPP
#define MODEL_ERROR_HPP

#include <radiorandom/model/generic/model.hpp>

namespace content {
    struct error : public generic {
        int code;
        std::string message;
    };
}


#endif // MODEL_ERROR_HPP
