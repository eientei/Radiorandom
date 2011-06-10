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
/// init IO
#define pio_init() { setlocale(LC_ALL,""); SetConsoleOutputCP(CP_UTF8); }
/// convert multibyte string to widechar one
#define pio_mbstowcs(dest,source,length) MultiByteToWideChar(CP_UTF8,0,(source),-1,(dest),(length))
/// convert widechar string to multibyte one
#define pio_wcstombs(dest,source,length) return WideCharToMultiByte(CP_UTF8, 0, (source), -1, (dest), (length), NULL, NULL);;
#else
/// init IO
#define pio_init() setlocale(LC_ALL,"")
/// convert multibyte string to widechar one
#define pio_mbstowcs(dest,source,length) mbstowcs((dest),(source),(length))
/// convert widechar string to multibyte one
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

