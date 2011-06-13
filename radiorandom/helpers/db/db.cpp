#include <radiorandom/helpers/db/db.h>


/// @file

void helpers::db::sqlfy_pattern(std::string &s) {
	std::string::iterator it;
	for (it = s.begin(); it != s.end(); it++) {
		if (*it == '*') *it = '%';
	}
}



std::string helpers::db::sqlfy_pseudo(cppdb::session &sql, const std::string &s, bool negate) {
	std::string q;
	size_t delim = s.find(":");
	std::string colname = sql.escape(s.substr(0,delim));
	std::string value = sql.escape(s.substr(delim+1));
	if (value.find("*") != std::string::npos) {
		helpers::db::sqlfy_pattern(value);
		q = colname;
		if (negate) q += " NOT";
		q += " LIKE '" + value + "'";
		return q;
	}
	if (value.find("..") > 0 && value.find("..") < value.length() - 2) {
		int v_min,v_max;
		sscanf(value.c_str(),"%d..%d",&v_min,&v_max);
		char min[1024];
		char max[1024];
		snprintf(min,1024,"%d",v_min);
		snprintf(max,1024,"%d",v_max);
		if (negate) {
			q = "(" + colname + " < " + min + " OR " + colname + " > " + max +  ")";
		} else {
			q = "(" + colname + " >= " + min + " AND " + colname + " <= " + max +  ")";
		}
	} else if (value.find("<=") == 0 || value.find("..") == 0) {
		value.erase(0,2);
		if (negate) {
			q = "(" + colname + " > '" + value + "')";
		} else {
			q = "(" + colname + " <= '" + value + "')";
		}
	} else if (value.find(">=") == 0 || value.find("..") == (value.length() - 2)) { 
		if (value.find(">=") == 0) value.erase(0,2);
		if (value.find("..") == (value.length() -2)) value.erase(value.length() - 2);
		if (negate) {
			q = "(" + colname + " < '" + value + "')";
		} else {
			q = "(" + colname + " >= '" + value + "')";
		}
	} else if (value[0] == '>') {
		value.erase(0,1);
		if (negate) {
			q = "(" + colname + " <= '" + value + "')";
		} else {
			q = "(" + colname + " > '" + value + "')";
		}
	} else if (value[0] == '<') {
		value.erase(0,1);
		if (negate) {
			q = "(" + colname + " >= '" + value + "')";
		} else {
			q = "(" + colname + " < '" + value + "')";
		}
	} else {
		if (negate) {
			q = "( NOT " + colname + " = '" + value + "')";
		} else {
			q = "(" + colname + " = '" + value + "')";
		}
	}
	return q;
}



std::string helpers::db::tags_parse(cppdb::session &sql, std::string url, std::string base, std::string table) {
	std::string::iterator sit;
	std::vector<std::string>::iterator vit;
	
	std::vector<std::string> tags;
	
	std::vector<std::string> and_tags;
	std::vector<std::string> or_tags;
	
	std::vector<std::string> and_yes_tags;
	std::vector<std::string> and_not_tags;
	std::vector<std::string> or_yes_tags;
	std::vector<std::string> or_not_tags;
	
	std::vector<std::string> pattern_and_yes_tags;
	std::vector<std::string> pattern_and_not_tags;
	std::vector<std::string> pattern_or_yes_tags;
	std::vector<std::string> pattern_or_not_tags;
	
	std::vector<std::string> pseudo_and_yes_tags;
	std::vector<std::string> pseudo_and_not_tags;
	std::vector<std::string> pseudo_or_yes_tags;
	std::vector<std::string> pseudo_or_not_tags;
	
	std::string sql_and_yes;
	std::string sql_and_not;
	std::string sql_or_yes;
	std::string sql_or_not;
	
	std::string sql_result;
	
	std::string tag;
	
	/******************************************************************
	 *                        FIRST SORT PASS                         *
	 ******************************************************************/
	size_t base_pos = url.find(base);
	if (base_pos != std::string::npos) url.erase(0,base_pos+base.length());
	while (url[0] == '/' || url[0] == '+') url.erase(0,1);
	for (sit = url.begin(); sit != url.end(); sit++) {
		if (*sit == '+') {
			tags.push_back(helpers::format::uri_unescape(tag));
			tag.erase();
			continue;
		}
		tag.push_back(*sit);
	}
	if (!tag.empty()) {
		tags.push_back(helpers::format::uri_unescape(tag));
		tag.erase();
	}
	

	
	/******************************************************************
	 *                       SECOND SORT PASS                         *
	 ******************************************************************/
	
	for (vit = tags.begin(); vit != tags.end(); vit++) {
		if ((*vit)[0] == '~') {
			vit->erase(0,1);
			or_tags.push_back(*vit);
		} else {
			and_tags.push_back(*vit);
		}
	}

	
	/******************************************************************
	 *                        THIRD SORT PASS                         *
	 ******************************************************************/

	for (vit = or_tags.begin(); vit < or_tags.end(); vit++) {
		if ((*vit)[0] == '-') {
			vit->erase(0,1);
			if (vit->find(":") == std::string::npos) {
				if (vit->find("*") == std::string::npos) {
					or_not_tags.push_back(*vit);
				} else { // if asterisk in present
					pattern_or_not_tags.push_back(*vit);
				}
			} else { // if colon in present
				pseudo_or_not_tags.push_back(*vit);
			}
		} else { // if not NOT
			if (vit->find(":") == std::string::npos) {
				if (vit->find("*") == std::string::npos) {
					or_yes_tags.push_back(*vit);
				} else { // if asterisk in present
					pattern_or_yes_tags.push_back(*vit);
				}
			} else { // if colon in present
				pseudo_or_yes_tags.push_back(*vit);
			}
		}
	}
	or_tags.clear();
	
	
	for (vit = and_tags.begin(); vit < and_tags.end(); vit++) {
		if ((*vit)[0] == '-') {
			vit->erase(0,1);
			if (vit->find(":") == std::string::npos) {
				if (vit->find("*") == std::string::npos) {
					and_not_tags.push_back(*vit);
				} else { // if asterisk in present
					pattern_and_not_tags.push_back(*vit);
				}
			} else { // if colon in present
				pseudo_and_not_tags.push_back(*vit);
			}
		} else { // if not NOT
			if (vit->find(":") == std::string::npos) {
				if (vit->find("*") == std::string::npos) {
					and_yes_tags.push_back(*vit);
				} else { // if asterisk in present
					pattern_and_yes_tags.push_back(*vit);
				}
			} else { // if colon in present
				pseudo_and_yes_tags.push_back(*vit);
			}
		}
	}
	and_tags.clear();
	



	/******************************************************************
	 *                           SQL PLAIN                            *
	 ******************************************************************/
	
	for (vit = and_not_tags.begin(); vit < and_not_tags.end(); vit++) {
		if (vit != and_not_tags.begin()) sql_and_not += ",";
		sql_and_not += sql.escape(*vit);
	}
	if (!sql_and_not.empty()) sql_and_not = 
		"(NOT tags @> '{" + sql_and_not + ")')";
	and_not_tags.clear();
	 
	 
	for (vit = and_yes_tags.begin(); vit < and_yes_tags.end(); vit++) {
		if (vit != and_yes_tags.begin()) sql_and_yes += ",";
		sql_and_yes += sql.escape(*vit);
	}
	if (!sql_and_yes.empty()) 
		sql_and_yes = "(tags @> '{" + sql_and_yes + ")')";
	and_yes_tags.clear();
	
	for (vit = or_not_tags.begin(); vit < or_not_tags.end(); vit++) {
		if (vit != or_not_tags.begin()) sql_or_not += ",";
		sql_or_not += sql.escape(*vit);
	}
	if (!sql_or_not.empty()) sql_or_not = 
		"(NOT tags && '{" + sql_or_not + ")')";
	or_not_tags.clear();
	
	for (vit = or_yes_tags.begin(); vit < or_yes_tags.end(); vit++) {
		if (vit != or_yes_tags.begin()) sql_or_yes += ",";
		sql_or_yes += sql.escape(*vit);
	}
	if (!sql_or_yes.empty()) 
		sql_or_yes = "(tags && '{" + sql_or_yes + ")')";
	or_yes_tags.clear();
	
	
	/******************************************************************
	 *                          SQL PATTERN                           *
	 ******************************************************************/

	for (vit = pattern_and_not_tags.begin(); vit < pattern_and_not_tags.end(); vit++) {
		if (vit == pattern_and_not_tags.begin() && !sql_and_not.empty())
			sql_and_not += " AND ";
		if (vit != pattern_and_not_tags.begin()) sql_and_not += " AND ";
		helpers::db::sqlfy_pattern(*vit);
		sql_and_not += "(NOT tags @> liketags ('" + sql.escape(*vit) + "'))";
	}
	pattern_and_not_tags.clear();
	
	for (vit = pattern_and_yes_tags.begin(); vit < pattern_and_yes_tags.end(); vit++) {
		if (vit == pattern_and_yes_tags.begin() && !sql_and_yes.empty())
			sql_and_yes += " AND ";
		if (vit != pattern_and_yes_tags.begin()) sql_and_yes += " AND ";
		helpers::db::sqlfy_pattern(*vit);
		sql_and_yes += "(tags @> liketags ('" + sql.escape(*vit) + "'))";
	}
	pattern_and_yes_tags.clear();
	
	for (vit = pattern_or_not_tags.begin(); vit < pattern_or_not_tags.end(); vit++) {
		if (vit == pattern_or_not_tags.begin() && !sql_or_not.empty())
			sql_or_not += " OR ";
		if (vit != pattern_or_not_tags.begin()) sql_or_not += " OR ";
		helpers::db::sqlfy_pattern(*vit);
		sql_or_not += "(NOT tags && liketags ('" + sql.escape(*vit) + "'))";
	}
	pattern_or_not_tags.clear();
	
	for (vit = pattern_or_yes_tags.begin(); vit < pattern_or_yes_tags.end(); vit++) {
		if (vit == pattern_or_yes_tags.begin() && !sql_or_yes.empty())
			sql_or_yes += " OR ";
		if (vit != pattern_or_yes_tags.begin()) sql_or_yes += " OR ";
		helpers::db::sqlfy_pattern(*vit);
		sql_or_yes += "(tags && liketags ('" + sql.escape(*vit) + "'))";
	}
	pattern_or_yes_tags.clear();
	
	/******************************************************************
	 *                          SQL PSEUDO                            *
	 ******************************************************************/
	
	for (vit = pseudo_and_not_tags.begin(); vit < pseudo_and_not_tags.end(); vit++) {
		if (vit == pseudo_and_not_tags.begin() && !sql_and_not.empty())
			sql_and_not += " AND ";
		if (vit != pseudo_and_not_tags.begin()) sql_and_not += " AND ";
		sql_and_not += helpers::db::sqlfy_pseudo(sql,*vit,true);
	}
	pseudo_and_not_tags.clear();
	
	for (vit = pseudo_and_yes_tags.begin(); vit < pseudo_and_yes_tags.end(); vit++) {
		if (vit == pseudo_and_yes_tags.begin() && !sql_and_yes.empty())
			sql_and_yes += " AND ";
		if (vit != pseudo_and_yes_tags.begin()) sql_and_yes += " AND ";
		sql_and_yes += helpers::db::sqlfy_pseudo(sql,*vit,false);
	}
	pseudo_and_yes_tags.clear();
	
	for (vit = pseudo_or_not_tags.begin(); vit < pseudo_or_not_tags.end(); vit++) {
		if (vit == pseudo_or_not_tags.begin() && !sql_or_not.empty())
			sql_or_not += " OR ";
		if (vit != pseudo_or_not_tags.begin()) sql_and_not += " OR ";
		sql_or_not += helpers::db::sqlfy_pseudo(sql,*vit,true);
	}
	pseudo_or_not_tags.clear();
	
	for (vit = pseudo_or_yes_tags.begin(); vit < pseudo_or_yes_tags.end(); vit++) {
		if (vit == pseudo_or_yes_tags.begin() && !sql_or_yes.empty())
			sql_or_yes += " OR ";
		if (vit != pattern_or_yes_tags.begin()) sql_or_yes += " OR ";
		sql_or_yes += helpers::db::sqlfy_pseudo(sql,*vit,false);
	}
	pseudo_or_yes_tags.clear();
	
	/******************************************************************
	 *                         SQL COMBINE                            *
	 ******************************************************************/
	
	if (!sql_and_yes.empty()) {
		sql_result += "( ";
		sql_result += sql_and_yes;
	}
	if (!sql_and_not.empty()) {
		if (!sql_result.empty()) sql_result += " AND ";
		else sql_result += "( ";
		sql_result += sql_and_not;
	}
	if (!sql_or_yes.empty()) {
		if (!sql_result.empty()) sql_result += " ) AND ( ";
		else sql_result += "( ";
		sql_result += sql_or_yes;
	}
	if (!sql_or_not.empty()) {
		if (sql_or_yes.empty() && !sql_result.empty()) sql_result += " ) AND ( ";
		else if (sql_result.empty()) sql_result += "( ";
		sql_result += sql_or_not;
	}
	sql_result += " )";
	
	return sql_result;
}
