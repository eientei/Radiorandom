#ifndef STATIC_H
#define STATIC_H

///@file

#include <Generic/DB/Interact/Interact.h>
#include <Generic/Data/Format/Format.h>


/// Static instances
namespace Static {
	namespace Data {
		static Generic::Data::Format Format;
	}
	/// DB instances
	namespace DB {
		/// DB Interaction instance
		static Generic::DB::Interact Interact;
	}

}
#endif
