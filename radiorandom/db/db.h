#ifndef RADIORANDOM_DB
#define RADIORANDOM_DB

#include <cppdb/frontend.h>

namespace db {
	namespace {
		cppdb::session i_sql;
	}
	void connect();
	cppdb::session sql();
	typedef cppdb::result result;
}

#endif
