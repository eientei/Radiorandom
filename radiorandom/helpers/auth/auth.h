#ifndef RADIORANDOM_HELPERS_AUTH
#define RADIORANDOM_HELPERS_AUTH

/// @file

#include <string>
#include <radiorandom/db/db.h>
#include <radiorandom/models/master/generic.h>
#include <radiorandom/helpers/hash/hash.h>
namespace helpers {
	class auth {
		public:
			static void auth_user(models::master::generic &c, std::string session);
			static std::string make_session(std::string username);
			static bool session_exist(std::string session);
			static bool user_exist(std::string username, std::string password_hash, bool raw = false);
	};
}
#endif
