#ifndef RADIORANDOM_DATA_MENUSET
#define RADIORANDOM_DATA_MENUSET

#include <vector>
#include <string>

/// @file

using namespace std;

/// Menu item representation
class menu_item {
	public:
		string name; ///< name of item
		string href; ///< link to item
	public:
		/// default constructor
		menu_item();
		/// shorty constructor
		menu_item(string name, string href);
};

/// Helper for models
typedef vector<menu_item> menu_set;

#endif

