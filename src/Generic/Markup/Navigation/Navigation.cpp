#include "Navigation.h"

namespace {
	std::string GenNavigationHelperHelper(int page, int current, std::string prefix, std::string chr="") {
		std::string pagestr = Generic::Data::Format().ToString(page);
		std::string href_class = "current";
		std::string href = "";
		if (chr.empty()) chr = pagestr;
		if (page != current) {
			href_class = "rest";
			href = " href = \"" + prefix + "&amp;page=" + pagestr + "\"";
		}
		return "<a class=\"" + href_class + "\"" + href + ">" + chr + "</a>";

	}

	std::string GenNavigationHelper(int begin,int end,int current, std::string prefix) {
		std::string result;
		for (int i=begin; i <= end; i++) {
			result += GenNavigationHelperHelper(i,current,prefix);
		}
		return result;
	}
}

std::string Generic::Markup::Navigation::GenNavigation(Generic::Data::Content::SetUsers &set) {
	std::string result;
	std::string prefix = set.url.prefix + set.url.infix;
	int total_pages = set.total_items / set.page_size;
	if (set.total_items % set.page_size) total_pages += 1;
	if (total_pages <= 1) return "";
	int cc;
	cc = (set.page-1); if (cc < 1) cc = 1;
	result += GenNavigationHelperHelper(cc,set.page,prefix,"&lt;&lt;");
	if (total_pages <= 7) {
		result += GenNavigationHelper(1,total_pages,set.page,prefix);
	} else {
		if (set.page <= 5) {
			int max = 5;
			if (set.page >= 4) max += 1;
			if (set.page >= 5) max += 1;
			result += GenNavigationHelper(1,max,set.page,prefix);
			result += "...";
			result += GenNavigationHelperHelper(total_pages,set.page,prefix);
		} else if (set.page >= (total_pages - 4)) {
			int min = total_pages - 4;
			if (set.page <= (total_pages - 3)) min -= 1;
			if (set.page <= (total_pages - 2)) min -= 1;
			result += GenNavigationHelperHelper(1,set.page,prefix);
			result += "...";
			result += GenNavigationHelper(min,total_pages,set.page,prefix);
		} else {
			result += GenNavigationHelperHelper(1,set.page,prefix);
			result += "...";
			result += GenNavigationHelper(set.page-2,set.page+2,set.page,prefix);
			result += "...";
			result += GenNavigationHelperHelper(total_pages,set.page,prefix);
		}
	}
	cc = (set.page+1); if (cc > total_pages) cc = total_pages;
	result += GenNavigationHelperHelper(cc,set.page,prefix,"&gt;&gt;");
	return result;
}
	
