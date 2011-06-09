#include "PString.h"

/// @file

void PString::widechar_to_data(const wchar_t *text,int length) {
	if (length < 0)
		length = wcslen(text);
	for (int i=0; i < length; i++) {
		data.push_back(text[i]);
	}
}

void PString::data_to_widechar() {
	if (wstr != NULL) {
		delete[] wstr;
		wstr = NULL;
	}
	
	size_t length = data.size();
	
	wstr = new wchar_t[length + 1];
	wstr_len = length + 1;
	
	std::vector<wchar_t>::iterator it;
	int i;
	for (i=0, it = data.begin(); it != data.end(); it++, i++) {
		wstr[i] = *it;
	}
	wstr[i] = '\0';
}

void PString::init() {
	cstr = NULL;
	wstr = NULL;
	cstr_len = 0;
	wstr_len = 0;
}

bool PString::iswnull(wchar_t ch) {
	return (ch == '\0');
}


PString::PString() {
	init();
}

PString::PString(const wchar_t *source, int length) {
	init();
	widechar_to_data(source,length);
}

PString::PString(const char *source, int length) {
	init();
	wchar_t *wcs = NULL;
	pioh_mbtowc(&wcs,source,length);
	widechar_to_data(wcs,length);
	delete[] wcs;
}

PString::PString(const PString &r) {
	init();
	data = r.data;
}

PString::~PString() {
	delete[] cstr;
	delete[] wstr;
}




PString & PString::operator=(PString const &r) {
	if (&r == this) return *this;
	data = r.data;
	return *this;
}

wchar_t & PString::operator[](size_t i) {
	return data[i];
}



std::vector<wchar_t> PString::get_raw_data() const {
	return data;
}

void PString::append(const PString &r) {
	std::vector<wchar_t> oth_data = r.get_raw_data();
	for (size_t i=0; i < oth_data.size(); i++) {
		data.push_back(oth_data[i]);
	}
}

size_t PString::length() {
	return data.size();
}

const char *PString::c_str() {
	if (cstr != NULL) {
		delete[] cstr;
		cstr = NULL;
	}
	data_to_widechar();
	cstr_len = pioh_wctomb(&cstr,wstr,data.size());
	return cstr;
}

size_t PString::c_str_length() {
	c_str();
	return cstr_len;
}

const wchar_t *PString::w_str() {
	data_to_widechar();
	return wstr;
}

void PString::clear() {
	data.clear();
}

void PString::resize(size_t size) {
	data.resize(size);
}

void PString::filter(bool (*predicate)(wchar_t)) {
	for (size_t i=0; i < data.size(); i++) {
		if ((*predicate)(data[i])) {
			data.erase(data.begin()+i);
		}
	}
}

void PString::dropwhile_left(bool (*predicate)(wchar_t)) {
	for (size_t i=0; i < data.size() && (*predicate)(data[i]); i++) {
		data.erase(data.begin()+i);
	}
}

void PString::dropwhile_right(bool (*predicate)(wchar_t)) {
	if (data.size() < 2) return;
	for (int i=data.size()-1; i >= 0; i--) {
		if ((*predicate)(data[i])) data.erase(data.begin()+i);
	}
}

void PString::filter_control() {
	filter((bool(*)(wchar_t))iswcntrl);
}

void PString::trim_right() {
	dropwhile_right((bool(*)(wchar_t))iswcntrl);
}

bool operator<(PString const& l, PString const& r) {
	return l.get_raw_data() < r.get_raw_data();
}

PString operator+(PString const& l, PString const& r) {
	PString pstr(l);
	pstr.append(r);
	return pstr;
}

bool operator==(PString const& l, PString const& r) {
	return l.get_raw_data() == r.get_raw_data();
}

bool operator!=(PString const& l, PString const& r) {
	return l.get_raw_data() != r.get_raw_data();
}
