#ifndef GENERIC_DATA_CONTENT_SETUSERS
#define GENERIC_DATA_CONTENT_SETUSERS

/// @file

#include <Generic/Generic.h>
#include <Generic/Data/Content/Set/Set.h>


/// Menu content data strcuture
class Generic::Data::Content::SetUsers : public Set {
	public:
		/// Menu item structure
		class ItemUser {
			public:
				int id;                    ///< User ID
				int access;                ///< User access
				std::string name;          ///< User name
				std::string password_hash; ///< User password hash
				std::string email;         ///< User email
				int joined;                ///< User joining time
				int score;                 ///< User score
				int changer;               ///< User last changer
				int changed;               ///< User last chaging date
				bool authed;               ///< If user logged in
				ItemUser() :
					id(0),
					access(0),
					joined(0),
					score(0),
					changer(0),
					changed(0),
					authed(false)
				{}
				/// Usual constructor
				ItemUser(
					int id,
					int access,
					std::string name,
					std::string password_hash,
					std::string email,
					int joined,
					int score,
					int changer,
					int changed,
					bool authed = false
				) :
					id(id), 
					access(access),
					name(name),
					password_hash(password_hash),
					email(email),
					joined(joined),
					score(score),
					changer(changer),
					changed(changed),
					authed(authed)
				{}
		};
	public:
		std::vector<ItemUser> items; ///< Items data
	public:
		SetUsers() :
			Set()
		{}
		/// Usual constructor
		SetUsers(int page, int page_size, ContentURL url, bool show_sort=true) :
			Set(page,page_size,url,show_sort)
		{}
	public:
		/// Adds item to set
		void AddItem(ItemUser item) {
			items.push_back(item);
		}

};
#endif
