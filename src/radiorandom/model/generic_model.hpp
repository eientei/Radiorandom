#ifndef MODEL_GENERIC_MODEL_HPP
#define MODEL_GENERIC_MODEL_HPP

#include <string>

#include <cppcms/view.h>  

namespace content {
	struct generic_model : public cppcms::base_content {
		bool is_installed;
	};
}

#endif
