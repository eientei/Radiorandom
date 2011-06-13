#include <radiorandom/db/db.h>

void db::connect() {
	i_sql = cppdb::session("postgresql:host=127.0.0.1;user=radiorandom;password=ignorethis");
}

cppdb::session db::sql() {
	return  i_sql;
}
