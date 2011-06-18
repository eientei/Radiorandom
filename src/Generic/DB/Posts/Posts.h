#ifndef GENERIC_DB_POSTS
#define GENERIC_DB_POSTS

/// @file

#include <string>

#include <Generic/Generic.h>
#include <Static/Static.h>

/// Users database routines
class Generic::DB::Posts {
	public:
		
		/// Fetch postscount
		/// 
		/// @return number of posts
		int PostsCount();
		
		/// Fetch total posts size
		///
		/// @return size in bytes
		int PostsSize();
};

#endif
