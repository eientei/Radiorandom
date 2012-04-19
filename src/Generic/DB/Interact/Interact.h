#ifndef GENERIC_DB_INTERACT
#define GENERIC_DB_INTERACT

/// @file

#include <string>

#include <cppdb/frontend.h>
#include <cppdb/mutex.h>
#include <fstream>

#include <Generic/Generic.h>

/// Filesystem checks class. HARDCODED.
class Generic::DB::Interact {
	private:
		cppdb::session sql;         ///< Connection to database
		std::string connect_string; ///< Connection string for session.
		cppdb::mutex block;         ///< Mutex lock

	public:
		Interact()
		{
			connect_string = "postgresql:host=127.0.0.1;user=radiorandom;password=ignorethis";
			sql = cppdb::session(connect_string);

		}
		/// Usual constructor
		Interact (std::string q) {
			connect_string = q;
			sql = cppdb::session(connect_string);
		}
		
		/// Lock the mutex
		void Lock() {
			block.lock();
		}
		
		/// Unlock the mutex
		void Unlock() {
			block.unlock();
		}
		
		/// Exec manipulator
		///
		/// \param [in] stmt sql statement exec to
		static void Exec(cppdb::statement &stmt) {
			cppdb::exec(stmt);
		}
		
		/// Loads schema from file and executes in place
		///
		/// \param [in] filepath to process
		void LoadSchema(std::string filepath);
		
		/// Escapes string
		///
		/// \param [in] what to escape;
		///
		/// @return escaped string
		std::string Escape(std::string what) {
			return sql.escape(what);
		}

		/// << Operator
		cppdb::statement operator<<(std::string q) {
			printf("%s\n",q.c_str());
			return sql << q;
		}
		/// Wrapper
		typedef cppdb::transaction Transaction;
		
		/// Wrapper
		typedef cppdb::result Result;
		
		/// Wrapper
		typedef cppdb::statement Statement;
};

#endif
