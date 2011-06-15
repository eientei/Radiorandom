#ifndef GENERIC_DB_USERS
#define GENERIC_DB_USERS

/// @file

#include <string>

#include <Generic/Generic.h>
#include <Generic/Data/Content/SetUsers/SetUsers.h>
#include <Generic/DB/Interact/Interact.h>
#include <Generic/Hash/SHA1/SHA1.h>

#include <Models/Master/Generic.h>

/// Users database routines
class Generic::DB::Users {
	public:
		/// Authentificate user in Model instance
		///
		/// \param [in,out] c is model populate to
		/// \param [in] session use to
		void AuthUser(Models::Master::Generic &c, std::string session);
		
		/// Make session from unique username
		///
		/// \param [in] username to use
		///
		/// @return resulting session on success or empty string on failure
		std::string MakeSession(std::string username);
		
		/// Checks whether such sesion exists
		///
		/// \param [in] session check to
		///
		/// @return true if session exist
		bool ExistSession(std::string session);
		
		/// Checks whether such user exist
		///
		/// \param [in] username check to
		/// \param [in] password check to
		/// \param [in] raw_password if true, password will be hashed first
		///
		/// @return true if user exist
		bool ExistUser(std::string username, std::string password, bool raw_password = false);

		/// Fills SetUsers
		///
		/// \param [in,out] s set to fill
		/// \param [in] r DB::Result to use
		///
		/// @return filled SetUsers set
		void FillSetUsers(Generic::Data::Content::SetUsers &s, Generic::DB::Interact::Result &r);
	
		/// Fills ItemUser strcuture with content from database result
		///
		/// \param [in,out] i input item structure
		/// \param [in] r result to use
		void FillItemUser(Generic::Data::Content::SetUsers::ItemUser &i, Generic::DB::Interact::Result &r);			
};

#endif
