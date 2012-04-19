#ifndef GENERIC_DB_TAGPARSER
#define GENERIC_DB_TAGPARSER

/// @file

#include <time.h>

#include <string>
#include <map>
#include <vector>

#include <Generic/Generic.h>
#include <Static/Static.h>


#include <uriparser/Uri.h>


#include <iostream>

/// Users database routines
class Generic::DB::TagParser {
	private:
		/// Input vector
		std::vector<std::string> input;
		
		/// Input AND vector
		std::vector<std::string> input_and;
		
		/// Input OR vector
		std::vector<std::string> input_or;
		
		/// +Tags
		std::vector<std::string> tags_and_yes;
		/// -Tags
		std::vector<std::string> tags_and_not;
		/// ~+Tags
		std::vector<std::string> tags_or_yes;
		/// ~-Tags
		std::vector<std::string> tags_or_not;
		
		/// +*Tags*
		std::vector<std::string> pattern_and_yes;
		/// -*Tags*
		std::vector<std::string> pattern_and_not;
		/// ~+*Tags*
		std::vector<std::string> pattern_or_yes;
		/// ~-*Tags*
		std::vector<std::string> pattern_or_not;
		
		/// +Name:Tag
		std::vector<std::string> pseudo_and_yes;
		/// -Name:Tag
		std::vector<std::string> pseudo_and_not;
		/// ~+Name:Tag
		std::vector<std::string> pseudo_or_yes;
		/// ~-Name:Tag
		std::vector<std::string> pseudo_or_not;
		
		/// AND
		std::string sql_and_yes;
		/// AND NOT
		std::string sql_and_not;
		/// OR
		std::string sql_or_yes;
		/// OR NOT
		std::string sql_or_not;
		
		/// SQL
		std::string sql;
		/// fields set
		static std::map<std::string,std::string> fields;
	private:
		/// Push tag to input vector
		void push_tag(std::string tag);
		/// Zero pass parsing stage	
		void categorize_zero_pass(std::string raw_query);
		/// First pass stage
		void categorize_first_pass();
		/// Second pass parse stage
		void categorize_second_pass(bool tags);
		/// Sqlfies for LIKE syntax
		static std::string sqlfy(std::string s, bool negate=false);
		/// Intersperce vector with string
		std::string intersperse(
			std::vector<std::string> arr,
			std::string sep,
			std::string (*processor)(std::string,bool) = NULL,
			bool negate = false
			
		);
		/// SQL first pass
		void generate_sql_first_pass();
		/// Scans date
		static std::string scandate(std::string value);
		/// Sqlfy pseudo tag
		static std::string sqlfy_pseudo(std::string tag, bool negate);
		/// Second pass generating sql
		void generate_sql_second_pass();
		/// Third apss of generating sql
		void generate_sql_third_pass();
	public:
		/// Get sql-query result
		std::string sql_where();
		/// Usual constructor
		TagParser(std::string raw_query, std::map<std::string,std::string> fields, bool tags=false) {
			this->fields = fields;
			categorize_zero_pass(raw_query);
			categorize_first_pass();
			categorize_second_pass(tags);
			
			generate_sql_first_pass();
			generate_sql_second_pass();
			generate_sql_third_pass();
			/*
			std::cout << sql_and_not << std::endl;
			std::cout << sql_and_yes << std::endl;
			std::cout << sql_or_not << std::endl;
			std::cout << sql_or_yes << std::endl;
			
			std::cout << "------------" << std::endl << sql << std::endl;
			
			printf("%d\n",input.size());
			*/
		}
};


#endif
