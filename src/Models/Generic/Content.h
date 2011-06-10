#ifndef RADIORANDOM_MODELS_GENERIC_CONTENT
#define RADIORANDOM_MODELS_GENERIC_CONTENT

/// @file

#include <string>
#include <Helpers/Navigation/NavigationGenerator.h>
#include <Helpers/Format/PassedTime.h>

using namespace std;

namespace model {

	/// Content model
	struct content :virtual public cppcms::base_content {
		bool many_items; ///< Is there more then one page of cotnetns
		int page_size;   ///< Page size
		int total_items; ///< total items in set
		int page;        ///< Current page
		string suffix;   ///< URL sufix
		string prefix;   ///< URL prefix
		content() {
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
}

#endif

