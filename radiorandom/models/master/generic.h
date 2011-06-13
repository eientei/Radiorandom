#ifndef RADIORANDOM_MODELS_MASTER_GENERIC
#define RADIORANDOM_MODELS_MASTER_GENERIC

#include <cppcms/view.h>


namespace models {
namespace master {
	struct generic :public cppcms::base_content {
		bool setted_up;
		bool user_authed;
		std::string user_name;
		int user_id;
		int user_access;
		generic() {
			setted_up = false;
			user_authed = false;
			user_id = 0;
			user_access = 0;
		}
	};
}
}



#endif
