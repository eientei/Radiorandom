#ifndef GENERIC_DATA_CONTENT_CONTENTURL
#define GENERIC_DATA_CONTENT_CONTENTURL

/// @file

#include <string>
#include <Generic/Generic.h>

/// Content URL representation
class Generic::Data::Content::ContentURL {
	public:
		std::string whole;  ///< url at one piece
		std::string prefix; ///< url prefix
		std::string infix;  ///< url infix
		std::string suffix; ///< url suffix
};

#endif
