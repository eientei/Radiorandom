#ifndef MODELS_GENERIC_INDEX
#define MODELS_GENERIC_INDEX

/// @file

#include <Generic/Data/Content/SetUsers/SetUsers.h>
#include <Generic/Data/Format/Format.h>

namespace Models {
	namespace Generic {
		/// Index struct.
		/// Used to display / index page.
		struct Index : public Models::Master::Master, public ::Generic::Data::Format {
			int index_files;      ///< Total files count
			int index_files_size; ///< Total files size
			
			Index() {
				index_files = 0;
				index_files_size = 0;
			}
		};
	}
}


#endif
