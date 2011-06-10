#ifndef RADIORANDOM_MODELS_GENERIC_INDEX
#define RADIORANDOM_MODELS_GENERIC_INDEX

/// @file

#include <Helpers/Format/FileSize.h>

namespace model {

	/// Index page model
	struct index :public master {
		size_t files;     ///< Number of files serving
		size_t filessize; ///< Size of all files
		
		index() {
			files = filessize = 0;
		}
		/// Format filter
		string format_filesize_filter(size_t size) {
			return format_filesize(size);
		}
	};

}

#endif

