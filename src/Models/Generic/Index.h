#ifndef MODELS_GENERIC_INDEX
#define MODELS_GENERIC_INDEX

/// @file

#include <Generic/Data/Format/Format.h>

namespace Models {
	namespace Generic {
		/// Index struct.
		/// Used to display / index page.
		struct Index : public Models::Master::Master {
			int index_files;      ///< Total files count
			int index_files_size; ///< Total files size
			::Generic::Data::Format formatter; ///< Formatter instance
			
			Index() {
				index_files = 0;
				index_files_size = 0;
			}
		};
	}
}


#endif
