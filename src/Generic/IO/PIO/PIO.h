#ifndef GENERIC_IO_PIO
#define GENERIC_IO_PIO

/// @file

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <assert.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <Generic/Generic.h>

/// PlainIO
class Generic::IO::PIO {
	public:
		/// Inits terminal IO
		PIO();
		
		/// Converts multibyte string to widechar one
		///
		/// \param [out] dest destination widechar string
		/// \param [in] source char string
		/// \param [in] length of the source string
		///
		/// @return number of widechar characters
		size_t mbstowcs(wchar_t * dest, const char * source,size_t length);
		
		/// Converts widechar string to multibyte one
		///
		/// \param [out] dest destination multibyte string
		/// \param [in] source widechar string
		/// \param [in] length of source string
		///
		/// @return number of characters
		inline size_t wcstombs(char * dest, const wchar_t * source, size_t length);

		/// Converts multibyte array to widechar one.
		///
		/// \param [out] dest is your destnation std::string to write to
		/// \param [in] source C std::string to convert from
		/// \param [in] length is optional length of source std::string
		/// @return length of resulting std::string
		size_t mbtowc(wchar_t **dest, const char *source, int length = -1);

		/// Converts widechar array to multibyte one.
		///
		/// \param [out] dest is your destination std::string; must be freed manualy
		/// \param [in] source is your widechar std::string to convert
		/// \param [in] length is optional length of the input std::string
		/// @return length of resulting std::string
		size_t wctomb(char **dest, const wchar_t *source,int length = -1);
		
		/// Calcualtes lengt of multibyte string in characters
		///
		/// \param [in] source string to process
		///
		/// @return length in characters [not bytes]
		size_t wclength(const char *source);
};
#endif
