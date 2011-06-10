#include <Data/UserSet/UserSet.h>

user_item::user_item() {
}

user_item::user_item(string username, int score, int access, int joined, int id) {
	this->username = username;
	this->score = score;
	this->access = access;
	this->joined = joined;
	this->id = id;
}
