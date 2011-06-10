#ifndef RADIORANDOM_MODELS_GENERIC_AUTH
#define RADIORANDOM_MODELS_GENERIC_AUTH

/// @file

namespace model {

	/// Authentification modl
	struct auth :public generic {
		bool user_auth;       ///< is user authed
		std::string username; ///< user name
		auth() {
			user_auth = false;
		}
	};

}
#endif

