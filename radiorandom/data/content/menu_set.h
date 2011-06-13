#ifndef RADIORANDOM_DATA_CONTENT_MENUSET
#define RADIORANDOM_DATA_CONTENT_MENUSET

#include <string>
#include <vector>


namespace data {
namespace content {
	class menu_item {
		public:
			std::string name;
			std::string href;
		public:
			menu_item();
			menu_item(std::string name, std::string href);
	};
	typedef std::vector<menu_item> menu_set;
}
}



#endif
