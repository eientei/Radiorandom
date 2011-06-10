#include <Apps/Server.h>

void controller::index() {
	model::index c;
	
	prepare(c,menu_item("[Index]","/"));
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result files = radiorandom_sql << "select sum(size),count(*) from files";
	files.next();
	c.files = files.get<int>("count(*)");
	if (!files.is_null("sum(size)"))
		c.filessize = files.get<int>("sum(size)");
	render("html_index",c);
}
