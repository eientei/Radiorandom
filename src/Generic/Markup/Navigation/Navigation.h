#ifndef GENERIC_MARKUP_NAVIGATION
#define GENERIC_MARKUP_NAVIGATION

#include <Generic/Generic.h>
#include <Generic/Data/Content/SetUsers/SetUsers.h>
#include <Generic/Data/Format/Format.h>

/// Navigation markup genrator
class Generic::Markup::Navigation {
	public:
		/// Actual generator function
		std::string GenNavigation(Generic::Data::Content::SetUsers &set);
};

#endif
