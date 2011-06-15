#ifndef GENERIC_DATA_CONTENT_SET
#define GENERIC_DATA_CONTENT_SET

/// @file

#include <vector>

#include <Generic/Generic.h>
#include <Generic/Data/Content/ContentURL/ContentURL.h>

/// Set of content items
class Generic::Data::Content::Set {
	public:
		size_t page;                            ///< Current page
		size_t page_size;                       ///< Page size
		ContentURL url;                         ///< Content URL
		bool show_sort;                         ///< Whether to show sorting methods
	Set() :
		page(0),
		page_size(0),		
		show_sort(false)
	{}
	/// Usual constructor
	Set(int page, int page_size, ContentURL url, bool show_sort = true) :
		page(page),
		page_size(page_size),
		url(url),
		show_sort(show_sort)
	{}
};

#endif
