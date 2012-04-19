#ifndef GENERIC_DB_USERS
#define GENERIC_DB_USERS

/// @file

#include <string>

#include <Generic/Generic.h>
#include <Generic/Data/Content/SetUsers/SetUsers.h>
#include <Static/Static.h>
#include <Generic/Hash/SHA1/SHA1.h>

#include <Models/Master/Generic.h>

/// Users database routines
class Generic::DB::Users {
	public:
			
		/// Fetch users count
		///
		/// \param [in] where clause
		///
		/// @return number of users
		int UsersCount(std::string where="");
		
		/// Fetch users count
		///
		/// \param [in] limit of set
		/// \param [in] offset of set 
		/// \param [in] sortby by what
		/// \param [in] order by what
		/// \param [in] where clause
		///
		/// @return users list
		Generic::DB::Interact::Result FetchUsersList(int limit, int offset,std::string sortby, std::string order, std::string where = "");
	
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
		
		/// Delete existing session
		///
		/// \param [in] hash of session
		void DeleteSession(std::string hash);
		
		/// Checks whether such sesion exists
		///
		/// \param [in] session check to
		///
		/// @return true if session exist
		bool ExistSession(std::string session);
		
		/// Checks whether such username exist
		///
		/// \param [in] username check to
		///
		/// @return true if user exist
		bool ExistUserName(std::string username);
		
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
		void FillSetUsers(Generic::Data::Content::SetUsers &s, Generic::DB::Interact::Result &r);
		
		/// Fill single user
		///
		/// \param [in,out] c is item user to fill
		/// \param [iid] user id
		void FillSingleUser(Generic::Data::Content::SetUsers::ItemUser &c, int iid);
	
		/// Fills ItemUser strcuture with content from database result
		///
		/// \param [in,out] i input item structure
		/// \param [in] r result to use
		void FillItemUser(Generic::Data::Content::SetUsers::ItemUser &i, Generic::DB::Interact::Result &r);			
		
		/// Populates access levels
		///
		/// \param [in] accesses to populate
		void PopulateAccessLevel(std::map<int,std::string> &accesses);
		
		/// Create new user
		///
		/// \param [in] username of new user
		/// \param [in] password of new user
		/// \param [in] email of new user
		/// \param [in] anonymous user if
		void CreateUser(std::string username, std::string password, std::string email, bool anonymous=false);
		
		/// Change email for user
		///
		/// \param [in] id of user
		/// \param [in] changer_id id of changing user
		/// \param [in] new_email to set
		void ChangeEmail(int id, int changer_id, std::string new_email);
		
		/// Change password for user
		///
		/// \param [in] id of user
		/// \param [in] changer_id id of changing user
		/// \param [in] new_password to set
		void ChangePassword(int id, int changer_id, std::string new_password);
};

#endif
