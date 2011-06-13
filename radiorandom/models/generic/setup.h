#ifndef RADIORANDOM_MODELS_GENERIC_SETUP
#define RADIORANDOM_MODELS_GENERIC_SETUP

namespace models {
namespace generic {
	struct setup :public models::master::master, public cppcms::form {
		cppcms::widgets::submit submit;
		setup() {
			submit.value("Setup");
			*this + submit;
		}
	};
}
}


#endif
