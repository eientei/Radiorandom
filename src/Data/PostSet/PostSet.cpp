#include <Data/PostSet/PostSet.h>

post_item::post_item() {
}

post_item::post_item(string filename, string filepath, string hash, int score, int size, int poster, int anon) {
	this->filename = filename;
	this->filepath = filepath;
	this->hash = hash;
	this->score = score;
	this->size = size;
	this->poster = poster;
	this->anon = anon;
}
