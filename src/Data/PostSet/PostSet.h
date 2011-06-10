#ifndef RADIORANDOM_DATA_POSTSET
#define RADIORANDOM_DATA_POSTSET

#include <vector>
#include <string>

/// @file

using namespace std;

/// Post item representation
class post_item {
	public:
		string filename; ///<
		string filepath;
		int score;
		int size;
		string tags;
		string hash;
		int poster;
		int anon;
		
	public:
		/// default constructor
		post_item();
		/// shorty constructor
		post_item(string filename, string filepath, string hash, int score, int size, int poster, int anon);
};

/// Helper for models
typedef vector<post_item> post_set;

#endif

