#ifndef RADIORANDOM_DATA_USERSET
#define RADIORANDOM_DATA_USERSET

#include <vector>
#include <string>

/// @file

using namespace std;

/// Menu item representation
class user_item {
	public:
		string username; ///< name of user
		int score;       ///< score of user
		int access;      ///< access of user
		int joined;      ///< joined date
		int id;          ///< id of user
		
	public:
		/// default constructor
		user_item();
		/// shorty constructor
		user_item(string username, int score, int access, int joined,int id);
};

/// Helper for models
typedef vector<user_item> user_set;

#endif

