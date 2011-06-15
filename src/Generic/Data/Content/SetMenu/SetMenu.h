#ifndef GENERIC_DATA_CONTENT_SETMENU
#define GENERIC_DATA_CONTENT_SETMENU

/// @file

#include <Generic/Generic.h>
#include <Generic/Data/Content/Set/Set.h>


/// Menu content data strcuture
class Generic::Data::Content::SetMenu : public Set {
	public:
		/// Menu item structure
		class ItemMenu {
			public:
				std::string name; ///< Link name
				std::string href; ///< URL href data
				ItemMenu() {}
				/// Usual constructor
				ItemMenu(std::string name, std::string href) :
					name(name), 
					href(href)
				{}
		};
	public:
		std::vector<ItemMenu> items; ///< Items data
	public:
		SetMenu() :
			Set()
		{}
		/// Usual constructor
		SetMenu(int page, int page_size, ContentURL url, bool show_sort=true) :
			Set(page,page_size,url,show_sort)
		{}
	public:
		/// Adds item to set
		void AddItem(ItemMenu item) {
			items.push_back(item);
		}

};
#endif
