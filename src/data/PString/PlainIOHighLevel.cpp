#include "PlainIO.h"

size_t pioh_mbtowc(wchar_t **dest, const char *source, int length) {
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
	buffsize = pio_mbstowcs(NULL,realsource,0);
	
	*dest = new wchar_t[buffsize+1];
	pio_mbstowcs(*dest,realsource,buffsize);
	(*dest)[buffsize] = '\0';
	
	delete[] realsource;
	
	return buffsize;
}

size_t pioh_wctomb(char **dest, const wchar_t *source,int length) {
	assert(*dest == NULL);
	wchar_t *realsource = new wchar_t[length+1];
	if (length < 0) {
		wcscpy(realsource,source);
	} else {
		wcsncpy(realsource,source,length);
	}
	realsource[length] = '\0';
	
	size_t buffsize = 0;
	buffsize = pio_wcstombs(NULL,realsource,0);
	
	*dest = new char[buffsize+1];
	pio_wcstombs(*dest,realsource,buffsize);
	(*dest)[buffsize] = '\0';
	
	delete[] realsource;
	
	return buffsize;
}
