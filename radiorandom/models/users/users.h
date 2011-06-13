#ifndef RADIORANDOM_MODELS_USERS_USERS
#define RADIORANDOM_MODELS_USERS_USERS

#include <radiorandom/models/users/content.h>


namespace models {
namespace users {
	struct users :virtual public models::master::master, public models::users::content {
	};
}
}



#endif
