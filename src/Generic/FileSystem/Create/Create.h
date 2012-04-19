#ifndef GENERIC_FILESYSTEM_CREATE
#define GENERIC_FILESYSTEM_CREATE

/// @file

#include <string>
#include <stdio.h>

#include <Generic/Generic.h>

/// Filesystem checks class
class Generic::FileSystem::Create {
	private:
		std::string filepath; ///< Default path test to
	public:
		Create() {}
		
		/// Usual constructor
		Create(std::string filepath) :
			filepath(filepath)
		{}
		
		/// Create if such file exists
		void CreateFile(std::string fpath = "");
};

#endif
