#include <radiorandom/data/content/user_set.h>

data::content::user_item::user_item(
) :
	id(0),
	access(0),
	joined(0),
	score(0),
	changer(0),
	changed(0)
{}
data::content::user_item::user_item(
	int id, 
	int access, 
	std::string name, 
	std::string password_hash,
	std::string email,
	int joined,
	int score,
	int changer,
	int changed
) :
	id(id),
	access(access),
	name(name),
	password_hash(password_hash),
	email(email),
	joined(joined),
	score(score),
	changer(changer),
	changed(changed)
{}
