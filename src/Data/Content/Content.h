#ifndef RADIORANDOM_DATA_CONTENT
#define RADIORANDOM_DATA_CONTENT

/// @file

#include <string>
#include <Helpers/Navigation/NavigationGenerator.h>
#include <Helpers/Format/PassedTime.h>
/// Content model
struct Content  {
	bool many_items; ///< Is there more then one page of cotnetns
	int page_size;   ///< Page size
	int total_items; ///< total items in set
	int page;        ///< Current page
	string suffix;   ///< URL sufix
	string infix;    ///< Infix of the query
	string prefix;   ///< URL prefix
	Content() {
		many_items = false;
		page = page_size = 1;
		total_items = 0;
	}
	/// Navigation generator filter
	string navigation_generator_filter(int page) {
		return navigation_generator(page,total_items,page_size,prefix);
	}
	/// Time passed filter
	string passed_time_filter(int time) {
		return passed_time(time);
	}
};


#endif

