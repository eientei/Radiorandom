#include <Helpers/Navigation/NavigationGenerator.h>

string navgen_helper(int begin, int end, int page, int pagesize, string prefix, int pn=1) {
	string result = "";
	string c_class,href;
	char buf[1024];
	
	for (int i=begin; i < end; i+=pagesize) {
		snprintf(buf,1024,"%d",pn);
		if (pn == page) {
			c_class="current";
			href="";
		} else {
			c_class = "rest";
			href = " href=\"" + prefix + "&amp;page=" + buf + "\"";
		}
		result += "<a class=\"" + c_class + "\"" + href + ">" + string(buf) + "</a>";
		pn++;
	}
	return result;
}

string navigation_generator(int page, int total, int pagesize, string prefix) {
	string result = "";
	int total_pages = total/pagesize;
	if (total%pagesize > 0) total_pages += 1;
	char buf[1024];
	string c_class="rest";
	string href="";
	if (page == 1) {
		result += "<a class=\"prev\">&lt;&lt;</a>";
	} else {
		snprintf(buf,1024,"%d",page-1);
		result += "<a class=\"prev-active\" href=\"" + prefix + "&amp;page=" + std::string(buf) + "\">&lt;&lt;</a>";
	}
	if (total_pages < 8) {
		result += navgen_helper(0,total,page,pagesize,prefix);
	} else {
		if (page > 5) {
			result += "<a class=\"rest\" href=\"" + prefix + "&amp;page=1\">1</a>";
			result += "...";
		}
		
		if (page < 6) {
			result += navgen_helper(0,(5+(page>=5&&2)+(page>5)+((page>=3) && abs(3-page)))*pagesize,page,pagesize,prefix);
		}
		
		if ((page >= 6) && (((total_pages - page) >= 5))) {
			result += navgen_helper((page-2)*pagesize,(page+3)*pagesize,page,pagesize,prefix,(page-2));
		}
		
		
		if ((total_pages - page) < 3) {
			result += navgen_helper(total-(5)*pagesize,total,page,pagesize,prefix,(total_pages - 4));
		} else if ((total_pages - page) < 4) {
			result += navgen_helper(total-(6)*pagesize,total,page,pagesize,prefix,(total_pages - 5));
		} else if ((total_pages - page) < 5) {
			result += navgen_helper(total-(7)*pagesize,total,page,pagesize,prefix,(total_pages - 6));
		}

		if ((total_pages - page) > 4) {
			snprintf(buf,1024,"%d",total_pages);
			result += "...";
			result += "<a class=\"rest\" href=\"" + prefix + "&amp;page=" + buf + "\">" + buf + "</a>";
		}
	}
	if (page == total_pages) {
		result += "<a class=\"next\">&gt;&gt;</a>";
	} else {
		snprintf(buf,1024,"%d",page+1);
		result += "<a class=\"next-active\" href=\"" + prefix + "&amp;page=" + std::string(buf) + "\">&gt;&gt;</a>";
	}
	return result;
}
