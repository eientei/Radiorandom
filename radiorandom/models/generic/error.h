#ifndef RADIORANDOM_MODELS_GENERIC_ERROR
#define RADIORANDOM_MODELS_GENERIC_ERROR


namespace models {
namespace generic {
	struct error :public models::master::master {
		int error_code;
		std::string error_message;
	};
}
}



#endif
