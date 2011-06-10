#ifndef RADIORANDOM_MODELS_POSTS
#define RADIORANDOM_MODELS_POSTS

/// @file

#include <Data/PostSet/PostSet.h>

namespace model {
	/// Posts model
	struct posts :public master, public content {
		string sortdir_filename; ///< Filename
		string sortdir_score;    ///< Score
		string sortdir_size;     ///< Filesize
		string sortdir_tags;     ///< File tags
		string sortdir_poster;   ///< File poster
		post_set postsset;       ///< Set of posts
		posts() {
			sortdir_filename = sortdir_score = sortdir_size = sortdir_tags = sortdir_poster = "desc";
		}
	};

}

#endif

