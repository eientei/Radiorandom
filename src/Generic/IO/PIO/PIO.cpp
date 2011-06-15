#include "PIO.h"

Generic::IO::PIO::PIO() {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif
	setlocale(LC_ALL,"");
}

size_t Generic::IO::PIO::mbstowcs(wchar_t * dest, const char * source,size_t length) {
#ifdef _WIN32
	return MultiByteToWideChar(CP_UTF8,0,(source),-1,(dest),(length));
#else
	return mbstowcs((dest),(source),(length));
#endif
}

size_t Generic::IO::PIO::wcstombs(char * dest, const wchar_t * source, size_t length) {
#ifdef _WIN32
	return WideCharToMultiByte(CP_UTF8, 0, (source), -1, (dest), (length), NULL, NULL);
#else
	return wcstombs((dest),(source),(length));
#endif
}

size_t Generic::IO::PIO::mbtowc(wchar_t **dest, const char *source, int length) {
	assert(*dest == NULL);
	char *realsource;

	if (length < 0) {
		length = strlen(source);
		realsource = new char[length+1];
		strncpy(realsource,source,length+1);
	} else {
		realsource = new char[length+1];
		strncpy(realsource,source,length+1);
	}
	realsource[length] = '\0';

	size_t buffsize = 0;
	buffsize = PIO::mbstowcs(NULL,realsource,0);
	
	*dest = new wchar_t[buffsize+1];
	mbstowcs(*dest,realsource,buffsize);
	(*dest)[buffsize] = '\0';
	
	delete[] realsource;
	
	return buffsize;
}

size_t Generic::IO::PIO::wctomb(char **dest, const wchar_t *source,int length) {
	assert(*dest == NULL);
	wchar_t *realsource = new wchar_t[length+1];
	if (length < 0) {
		wcscpy(realsource,source);
	} else {
		wcsncpy(realsource,source,length);
	}
	realsource[length] = '\0';
	
	size_t buffsize = 0;
	buffsize = wcstombs(NULL,realsource,0);
	
	*dest = new char[buffsize+1];
	wcstombs(*dest,realsource,buffsize);
	(*dest)[buffsize] = '\0';
	
	delete[] realsource;
	
	return buffsize;
}

size_t Generic::IO::PIO::wclength(const char *source) {
	return mbstowcs(NULL,source,0);
}
