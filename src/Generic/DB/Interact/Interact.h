#ifndef GENERIC_DB_INTERACT
#define GENERIC_DB_INTERACT

/// @file

#include <string>

#include <cppdb/frontend.h>

#include <Generic/Generic.h>

/// Filesystem checks class. HARDCODED.
class Generic::DB::Interact {
	private:
		std::string connect_string; ///< Connection string for session.
	public:
		Interact() {
			connect_string = "postgresql:host=127.0.0.1;user=radiorandom;password=ignorethis";
		}
		/// Usual constructor
		Interact (std::string q) {
			connect_string = q;
		}
		/// Exec manipulator
		///
		/// \param [in] stmt sql statement exec to
		static void Exec(cppdb::statement &stmt) {
			return cppdb::exec(stmt);
		}
		/// << Operator
		cppdb::statement operator<<(std::string q) {
			cppdb::session sql(connect_string);
			return sql << q;
		}
		/// Wrapper
		typedef cppdb::result Result;
		
		/// Wrapper
		typedef cppdb::statement Statement;
};

#endif
