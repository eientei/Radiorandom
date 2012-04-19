#include "TagParser.h"

std::map<std::string,std::string> Generic::DB::TagParser::fields;

void Generic::DB::TagParser::push_tag(std::string tag) {
	
	char *buf = new char[tag.length() + 1];
	strncpy(buf,tag.c_str(),tag.length());
	buf[tag.length()] = '\0';
	uriUnescapeInPlaceA(buf);
	std::string result(buf);
	delete[] buf;

	input.push_back(result);
}

/// Zero pass parsing stage	
void Generic::DB::TagParser::categorize_zero_pass(std::string raw_query) {

	std::string tag;
	std::string::iterator it;
	while (raw_query[0] == '/' || raw_query[0] == '+') raw_query.erase(0,1);
	raw_query += '+';
	for (it = raw_query.begin(); it != raw_query.end(); it++) {
		if (*it == '+' && tag.empty()) {
			continue;
		}
		if (*it == '+') {
			push_tag(tag);
			tag.erase();
			continue;
		}
		tag.push_back(*it);
	}
}
/// First pass stage
void Generic::DB::TagParser::categorize_first_pass() {
	std::vector<std::string>::iterator it;
	for (it = input.begin(); it != input.end(); it++) {
		if ((*it)[0] == '~') {
			it->erase(0,1);
			input_or.push_back(*it);
		} else {
			input_and.push_back(*it);
		}
	}
}
/// Second pass parse stage
void Generic::DB::TagParser::categorize_second_pass(bool tags) {
	std::vector<std::string>::iterator it;
	
	
	for (it = input_and.begin(); it != input_and.end(); it++) {
		if ((*it)[0] == '-') {
			it->erase(0,1);
			if (it->find(":") == std::string::npos) {
				if (!tags) continue;
				if (it->find("*") == std::string::npos) {
					tags_and_not.push_back(*it);
				} else {
					pattern_and_not.push_back(*it);
				}
			} else {
				pseudo_and_not.push_back(*it);
			}
		} else {
			if (it->find(":") == std::string::npos) {
				if (!tags) continue;
				if (it->find("*") == std::string::npos) {
					tags_and_yes.push_back(*it);
				} else {
					pattern_and_yes.push_back(*it);
				}
			} else {
				pseudo_and_yes.push_back(*it);
			}
		}
	}

	
	for (it = input_or.begin(); it != input_or.end(); it++) {
		if ((*it)[0] == '-') {
			it->erase(0,1);
			if (it->find(":") == std::string::npos) {
				if (!tags) continue;
				if (it->find("*") == std::string::npos) {
					tags_or_not.push_back(*it);
				} else {
					pattern_or_not.push_back(*it);
				}
			} else {
				pseudo_or_not.push_back(*it);
			}
		} else {
			if (it->find(":") == std::string::npos) {
				if (!tags) continue;
				if (it->find("*") == std::string::npos) {
					tags_or_yes.push_back(*it);
				} else {
					pattern_or_yes.push_back(*it);
				}
			} else {
				pseudo_or_yes.push_back(*it);
			}
		}
	}
}
/// Sqlfies for LIKE syntax
std::string Generic::DB::TagParser::sqlfy(std::string s, bool negate) {
	std::string::iterator it;
	for (it = s.begin(); it != s.end(); it++) {
		if (*it == '*') *it = '%';
	}
	return s;
}
/// Intersperce vector with string
std::string Generic::DB::TagParser::intersperse(
	std::vector<std::string> arr,
	std::string sep,
	std::string (*processor)(std::string,bool),
	bool negate
	
) {
	std::vector<std::string>::iterator it;
	std::string result;
	for (it = arr.begin(); it != arr.end(); it++) {
		if (it != arr.begin()) result += sep;
		std::string tmp = Static::DB::Interact.Escape(*it);
		if (processor != NULL) tmp = processor(tmp,negate);
		result += tmp;
	}
	return result;
}
/// SQL first pass
void Generic::DB::TagParser::generate_sql_first_pass() {
	std::string tmp;
	tmp = intersperse(tags_and_not,",");
	if (!tmp.empty()) sql_and_not += "(NOT tags @> '{" + tmp + "}')";
	tmp = intersperse(tags_and_yes,",");
	if (!tmp.empty()) sql_and_yes += "(tags @> '{" + tmp + "}')";
	tmp = intersperse(tags_or_not,",");
	if (!tmp.empty()) sql_or_not += "(NOT tags && '{" + tmp + "}')";
	tmp = intersperse(tags_or_yes,",");
	if (!tmp.empty()) sql_or_yes += "(tags && '{" + tmp + "}')";
	
	
	
	
	tmp = intersperse(pattern_and_not," AND ",sqlfy);
	if (!tmp.empty() && !sql_and_not.empty()) sql_and_not += " AND ";
	if (!tmp.empty()) sql_and_not += "(NOT tags @> liketags('" + tmp +"'))";
	
	tmp = intersperse(pattern_and_yes," AND ",sqlfy);
	if (!tmp.empty() && !sql_and_yes.empty()) sql_and_yes += " AND ";
	if (!tmp.empty()) sql_and_yes += "(tags @> liketags('" + tmp +"'))";
	
	tmp = intersperse(pattern_or_not," OR ",sqlfy);
	if (!tmp.empty() && !sql_or_not.empty()) sql_or_not += " OR ";
	if (!tmp.empty()) sql_or_not += "(NOT tags && liketags('" + tmp +"'))";
	
	tmp = intersperse(pattern_or_yes," OR ",sqlfy);
	if (!tmp.empty() && !sql_or_yes.empty()) sql_or_yes += " OR ";
	if (!tmp.empty()) sql_or_yes += "(tags && liketags('" + tmp +"'))";
}
/// Scans date
std::string Generic::DB::TagParser::scandate(std::string value) {
	int y,m,d;
	std::string prepvalue;
	y = m = d = 1;
	sscanf(value.c_str(),"%d-%d-%d",&y,&m,&d);
	if (y < 2011 || y > 9999) y = 2011; /// yeah, problem 10000.
	if (m < 1 || m > 12) m = 1;
	if (d < 1 || d > 31) d = 1;
	prepvalue = Static::Data::Format.ToString(y) + "-"
			  + Static::Data::Format.ToString(m) + "-"
			  + Static::Data::Format.ToString(d);
	return prepvalue;
}
/// Sqlfy pseudo tag
std::string Generic::DB::TagParser::sqlfy_pseudo(std::string tag, bool negate) {
	std::string result;
	size_t delim = tag.find(":");
	std::string colname = Static::DB::Interact.Escape(tag.substr(0,delim));
	std::string value = Static::DB::Interact.Escape(tag.substr(delim+1));
	printf("%s %s\n",colname.c_str(),fields[colname].c_str());
	
	if (false) {
	} else if (fields[colname] == "string") {
		if (negate) {
			result += " NOT ";
		}
		if (value.find("*") != std::string::npos) {
		value = sqlfy(value);
			result += "lower(" + colname + ") " + " LIKE lower('" + value + "')";
		} else {
			result += "lower(" + colname + ") " + " = lower('" + value + "')";
		}
		return "(" + result + ")";
	} else if (fields[colname] == "numeric" || fields[colname] == "date") {
		if (value.find("..") > 0 && value.find("..") < value.length() -2 ) {
			std::string min,max;
			if (fields[colname] == "numeric") {
				int v_min, v_max;
				sscanf(value.c_str(),"%d..%d",&v_min,&v_max);
				min = Static::Data::Format.ToString(v_min);
				max = Static::Data::Format.ToString(v_max);
			} else if (fields[colname] == "date") {
				int fy,sy;
				int fm,sm;
				int fd,sd;
				fy = fm = fd = 1;
				sy = sm = sd = 1;
				sscanf(value.c_str(),"%d-%d-%d..%*[^.]",&fy,&fm,&fd);
				sscanf(value.c_str(),"%*[^.]..%d-%d-%d",&sy,&sm,&sd);
				min = Static::Data::Format.ToString(fy) + "-"
					+ Static::Data::Format.ToString(fm) + "-"
					+ Static::Data::Format.ToString(fd);
				max = Static::Data::Format.ToString(sy) + "-"
					+ Static::Data::Format.ToString(sm) + "-"
					+ Static::Data::Format.ToString(sd);
				
			}
			if (negate) {
				return "(" + colname + " < " + min + " OR " + colname + " > " + max +  ")";
			} else {
				return "(" + colname + " >= " + min + " AND " + colname + " <= " + max +  ")";
			}
		} else if (value.find("<=") == 0 || value.find("..") == 0) {
			value.erase(0,2);
			std::string prepvalue;
			if (fields[colname] == "numeric") {
				prepvalue = Static::Data::Format.ToString(atoi(value.c_str()));
			} else if (fields[colname] == "date") {
				prepvalue = scandate(value);
			}
			if (negate) {
				return "(" + colname + " > '" + prepvalue + "')";
			} else {
				return "(" + colname + " <= '" + prepvalue + "')";
			}
		} else if (value.find(">=") == 0 || value.find("..") == (value.length() - 2)) {
			if (value.find(">=") == 0) value.erase(0,2);
			if (value.find("..") == (value.length() -2)) value.erase(value.length() - 2);
			std::string prepvalue;
			if (fields[colname] == "numeric") {
				prepvalue = Static::Data::Format.ToString(atoi(value.c_str()));
			} else if (fields[colname] == "date") {
				prepvalue = scandate(value);
			}
			if (negate) {
				return"(" + colname + " < '" + prepvalue + "')";
			} else {
				return "(" + colname + " >= '" + prepvalue + "')";
			}
		} else if (value[0] == '>') {
			value.erase(0,1);
			std::string prepvalue;
			if (fields[colname] == "numeric") {
				prepvalue = Static::Data::Format.ToString(atoi(value.c_str()));
			} else if (fields[colname] == "date") {
				prepvalue = scandate(value);
			}
			if (negate) {
				return "(" + colname + " <= '" + prepvalue + "')";
			} else {
				return "(" + colname + " > '" + prepvalue + "')";
			}
		} else if (value[0] == '<') {
			value.erase(0,1);
			std::string prepvalue;
			if (fields[colname] == "numeric") {
				prepvalue = Static::Data::Format.ToString(atoi(value.c_str()));
			} else if (fields[colname] == "date") {
				prepvalue = scandate(value);
			}
			if (negate) {
				return "(" + colname + " >= '" + prepvalue + "')";
			} else {
				return "(" + colname + " < '" + prepvalue + "')";
			}
		} else {
			std::string prepvalue;
			if (fields[colname] == "numeric") {
				prepvalue = Static::Data::Format.ToString(atoi(value.c_str()));
			} else if (fields[colname] == "date") {
				prepvalue = scandate(value);
			}
			if (negate) {
				return "( NOT " + colname + " = '" + prepvalue + "')";
			} else {
				return "(" + colname + " = '" + prepvalue + "')";
			}
		}
	} else {
		return "";
	}
	return result;
}
/// Second pass generating sql
void Generic::DB::TagParser::generate_sql_second_pass() {
	std::string tmp;
	tmp = intersperse(pseudo_and_not," AND ",sqlfy_pseudo,true);
	if (!tmp.empty() && !sql_and_not.empty()) sql_and_not += " AND ";
	if (!tmp.empty()) sql_and_not += tmp;

	tmp = intersperse(pseudo_and_yes," AND ",sqlfy_pseudo,false);
	if (!tmp.empty() && !sql_and_yes.empty()) sql_and_yes += " AND ";
	if (!tmp.empty()) sql_and_yes += tmp;

	tmp = intersperse(pseudo_or_not," OR ",sqlfy_pseudo,true);
	if (!tmp.empty() && !sql_or_not.empty()) sql_or_not += " OR ";
	if (!tmp.empty()) sql_or_not += tmp;

	tmp = intersperse(pseudo_or_yes," OR ",sqlfy_pseudo,false);
	if (!tmp.empty() && !sql_or_yes.empty()) sql_or_yes += " OR ";
	if (!tmp.empty()) sql_or_yes += tmp;
	
}
void Generic::DB::TagParser::generate_sql_third_pass() {
	if (!sql_and_not.empty() || !sql_and_yes.empty()) sql += "( ";
	if (!sql_and_yes.empty()) sql += "( " + sql_and_yes + " )";
	if (!sql.empty() && !sql_and_not.empty()) sql+= " AND ";
	if (!sql_and_not.empty()) sql += "( " + sql_and_not + " )";
	if (!sql.empty()) sql += " )";
	
	if (!sql.empty() && (!sql_or_not.empty() || !sql_or_yes.empty())) sql += " AND ";
	if (!sql_or_not.empty() || !sql_or_yes.empty()) sql += " ( ";
	if (!sql_or_not.empty()) sql += "( " + sql_or_not + " )";
	if (!sql_or_not.empty() && !sql_or_yes.empty())  sql+= " OR ";
	if (!sql_or_yes.empty()) sql += "( " + sql_or_yes + " )";
	if (!sql.empty() && (!sql_or_not.empty() || !sql_or_yes.empty())) sql += " )";
}
std::string Generic::DB::TagParser::sql_where() {
	return sql;
}
