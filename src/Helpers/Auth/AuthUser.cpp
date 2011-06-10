#include <Helpers/Auth/AuthUser.h>

/// @file

/// Auths user
///
/// \param [in] c auth struct
/// \param [in] session to check
void auth_user(model::auth &c, string session) {
	string username;
	if ((username = valid_session(session)).length() > 0) {
		c.user_auth = true;
		c.username = username;
	}
}
