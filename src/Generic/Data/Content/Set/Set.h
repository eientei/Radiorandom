#ifndef GENERIC_DATA_CONTENT_SET
#define GENERIC_DATA_CONTENT_SET

/// @file

#include <vector>

#include <Generic/Generic.h>
#include <Generic/Data/Content/ContentURL/ContentURL.h>

/// Set of content items
class Generic::Data::Content::Set {
	public:
		int total_items;                     ///< Items in total
		int page;                            ///< Current page
		int page_size;                       ///< Page size
		ContentURL url;                         ///< Content URL
		bool show_sort;                         ///< Whether to show sorting methods
	Set() :
		total_items(0),
		page(0),
		page_size(0),		
		show_sort(false)
	{}
	/// Usual constructor
	Set(int total_items, int page, int page_size, ContentURL url, bool show_sort = true) :
		total_items(total_items),
		page(page),
		page_size(page_size),
		url(url),
		show_sort(show_sort)
	{}
};

#endif
