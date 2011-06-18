#ifndef GENERIC_H
#define GENERIC_H

/// @file

/// Generic namespace, contains all other generic namespaces and generic
/// classes.
namespace Generic {
	/// IO classes
	namespace IO {
		class PIO;
	}
	/// Data classes
	namespace Data {
		/// Online content data types
		namespace Content {
			class ContentURL;
			class Set;
			class SetMenu;
			class SetUsers;
			class SetPosts; /////////////////////////////////////// TODO
		}
		class PString; //////////////////////////////////////////// TODO
		class Format;
	}
	/// Markup classes
	namespace Markup {
		class Menu; ////////// HARDCODED. Convinient though nonportable.
		class Navigation;
	}
	/// Hash classes
	namespace Hash {		
		class Hash;
		class SHA1;
		class MD5; //////////////////////////////////////////////// TODO
	}
	/// FileSystem-related classes
	namespace FileSystem {
		class Check;
		class Create;
	}
	/// Database classes
	namespace DB {
		class Interact; ////// HARDCODED. Convinient though nonportable.
		class TagParser;
		class Users;
		class Posts; ////////////////////////////////////////////// TODO
	}
}


#endif
