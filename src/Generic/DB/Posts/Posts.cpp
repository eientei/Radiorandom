#include "Posts.h"


int Generic::DB::Posts::PostsCount() {
	Static::DB::Interact.Lock();
	Generic::DB::Interact::Result posts_count = Static::DB::Interact << "select count(*) from posts";
	Static::DB::Interact.Unlock();
	posts_count.next();
	if (!posts_count.empty()) {
		return 0;
	}
	return posts_count.get<int>(0);
}

int Generic::DB::Posts::PostsSize() {
	Static::DB::Interact.Lock();
	Generic::DB::Interact::Result posts_size = Static::DB::Interact << "select count(*),sum(size) from posts";
	Static::DB::Interact.Unlock();
	posts_size.next();
	if (posts_size.get<int>(0) == 0) {
		return 0;
	}
	return posts_size.get<int>(1);
}
