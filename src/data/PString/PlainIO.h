#ifndef PLAINIO_H
#define PLAINIO_H

/// @file

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <assert.h>

#ifdef _WIN32

#include <windows.h>
/// Initialize terminal for unicode Input/Output.
#define pio_init() { setlocale(LC_ALL,""); SetConsoleOutputCP(CP_UTF8); }
/// Convert system's multibyte string to widechar string
///
/// \param [out] dest is your destination widechar buffer
/// \param [in] source is your C char source buffer
/// \param [in] length is required length of the source buffer
/// @return number of converted chars
#define pio_mbstowcs(dest,source,length) MultiByteToWideChar(CP_UTF8,0,(source),-1,(dest),(length))

/// Convert widechar string to system's multibyte string
///
/// \param [out] dest is your destination char buffer
/// \param [in] source is you widechar buffer
/// \param [in] length is required length of widechat buffer
/// @return number of converted bytes
#define pio_wcstombs(dest,source,length) return WideCharToMultiByte(CP_UTF8, 0, (source), -1, (dest), (length), NULL, NULL);;
#else
/// Initialize terminal for unicode Input/Output.
#define pio_init() setlocale(LC_ALL,"")
/// Convert system's multibyte string to widechar string
///
/// \param [out] dest is your destination widechar buffer
/// \param [in] source is your C char source buffer
/// \param [in] length is required length of the source buffer
/// @return number of converted chars
#define pio_mbstowcs(dest,source,length) mbstowcs((dest),(source),(length))
/// Convert widechar string to system's multibyte string
///
/// \param [out] dest is your destination char buffer
/// \param [in] source is you widechar buffer
/// \param [in] length is required length of widechat buffer
/// @return number of converted bytes
#define pio_wcstombs(dest,source,length) wcstombs((dest),(source),(length))

#endif


/// Converts multibyte array to widechar one.
///
/// \param [out] dest is your destnation string to write to
/// \param [in] source C string to convert from
/// \param [in] length is optional length of source string
/// @return length of resulting string
size_t pioh_mbtowc(wchar_t **dest, const char *source, int length = -1);

/// Converts widechar array to multibyte one.
///
/// \param [out] dest is your destination string; must be freed manualy
/// \param [in] source is your widechar string to convert
/// \param [in] length is optional length of the input string
/// @return length of resulting string
size_t pioh_wctomb(char **dest, const wchar_t *source,int length = -1);

#endif

