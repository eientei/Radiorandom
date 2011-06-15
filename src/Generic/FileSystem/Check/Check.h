#ifndef GENERIC_FILESYSTEM_CHECK
#define GENERIC_FILESYSTEM_CHECK

/// @file

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <Generic/Generic.h>


/// Filesystem checks class
class Generic::FileSystem::Check {
	private:
		std::string filepath; ///< Default path test to
	public:
		Check() {}
		
		/// Usual constructor
		Check(std::string filepath) :
			filepath(filepath)
		{}
		
		/// Checks if such file exists
		bool ExistFile(std::string fpath = "");
};

#endif
