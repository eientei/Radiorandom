#ifndef GENERIC_DATA_FORMAT
#define GENERIC_DATA_FORMAT

#include <map>
#include <string>
#include <sstream>

#include <uriparser/Uri.h>

#include <Generic/Generic.h>

/// Data formatting class
class Generic::Data::Format {
	private:
		/// Access levels, fetched from database
		std::map<int,std::string> user_access_levels;
	public:
	
		/// Converts number to a string representation
		///
		/// \param [in] value to convert
		///
		/// @return string representation
		template <typename T>
		std::string ToString(T value) {
			std::ostringstream result;
			result << value;
			return result.str();
		}
		
		/// Format file size to human-readable form.
		///
		/// \param [in] size is plain fole size
		///
		/// @return string representing human-readable size
		std::string FileSize(int size);
		
		/// Format UNIX timestamp to human-readable form.
		///
		/// \param [in] time since UNIX epoch
		///
		/// @return string representing human-readable time
		std::string TimePassed(int time);
		
		/// Unescape given URI.
		///
		/// Unescapes sequences like '%20' to corresponding characters
		///
		/// \param [in] uri to process
		///
		/// @return unescaped string
		std::string URIUnEscape(std::string uri);
		
		
		/// Convertes numeric access level to human readable form.
		///
		/// Converts numbers like -1,0,9999 to human readable form.
		///
		/// \param [in] access to convert
		///
		/// @return forammted string.
		std::string UserAccessFormat(std::string access);
};

#endif
