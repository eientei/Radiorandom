#ifndef CONTROLLER_POST_HPP
#define CONTROLLER_POST_HPP

#include <radiorandom/controller/generic/controller.hpp>

#include <radiorandom/model/post/index.hpp>
#include <radiorandom/model/post/list.hpp>
#include <radiorandom/model/post/upload.hpp>

namespace controller {
    class post : public generic {
        public:
            post(cppcms::service & srv);
        public:
            virtual void index();
            virtual void list();
            virtual void upload();
        protected:
            virtual void prepare(content::generic &c, std::string submenu_item);
    };
}


#endif // CONTROLLER_POST_HPP
