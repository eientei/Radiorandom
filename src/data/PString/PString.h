#ifndef PEASANTFORMER_Data_PString
#define PEASANTFORMER_Data_PString

/// @file

#include <vector>
#include <wctype.h>

#include "PlainIO.h"

/// Unicode-aware string class
class PString {
	private:
		std::vector<wchar_t> data; ///< Textual data
		char *cstr;                ///< C-string representation of data
		wchar_t *wstr;             ///< widechar representation of data
		size_t cstr_len;           ///< length of cstr
		size_t wstr_len;           ///< length of wstr
	private:
		
		/// Converts widechar data to internal text representation.
		///
		/// \param [in] text is widechar input string
		/// \param [in] length is Length of wchar data
		void widechar_to_data(const wchar_t *text,int length = -1);
		
		/// Converts internal text representation to widechar and store
		/// it in wstr.
		void data_to_widechar();
		
		/// Initializes things that a same for different constructors.
		void init();
		
		/// Simple function that chekcks if it's widechar parameter is
		/// '\0' and returns false if not.
		///
		/// \param [in] ch is character to test
		/// @return boolean
		bool iswnull(wchar_t ch);
	public:
		
		/// Dummy constructor.
		/// 
		PString();
		
		/// Widechar constructor.
		///
		/// \param [in] source is widechar 
		/// \param [in] length is optional length of the string
		PString(const wchar_t *source, int length = -1);
		
		/// C-string constructor.
		///
		/// \param [in] source is C source data
		/// \param [in] length is optional length of the string
		PString(const char *source, int length = -1);
		
		/// Copy constructor
		///
		/// \param [in] r is a source PString
		PString(const PString &r);
		
		/// Destructor
		~PString();
	public:
		
		/// Asignment operator
		///
		/// \param [in] r is right-hand expression
		/// @return PString refference
		PString & operator=(PString const &r);
		
		/// Subscripting operator
		/// 
		/// \param [in] i is index
		/// @return wchar refference
		wchar_t & operator[](size_t i);
	public:
		
		/// Get raw internal data representation.
		///
		/// @return internal data vector
		std::vector<wchar_t> get_raw_data() const;
	
		/// String appending
		///
		/// \param [in] r is right-hand expression
		void append(const PString &r);
		
		/// Length of the text stored in the PString
		///
		/// @return size_t length
		size_t length();
		
		/// C-string representation of PString.
		///
		/// @return C-string representation of data
		const char *c_str();
		
		/// Length of C string
		///
		/// @return C-string length
		size_t c_str_length();
		
		/// Widechar representation of PString.
		///
		/// @return widechar representation of data
		const wchar_t *w_str();
		
		/// Wipes PString
		void clear();
		
		/// Resizes PString.
		///
		/// \param [in] size of desired buffer size
		void resize(size_t size);
		
		/// Filters string using given predicate function
		///
		/// \param [in] predicate is predicate function
		void filter(bool (*predicate)(wchar_t));
		
		/// Drops characters from left as long as predicate function
		/// returns true.
		///
		/// \param [in] predicate is predicate function
		void dropwhile_left(bool (*predicate)(wchar_t));
		
		/// Drops characters from right as long as predicate function
		/// returns true.
		///
		/// \param [in] predicate is predicate function
		void dropwhile_right(bool (*predicate)(wchar_t));
		
		/// Shortname for filter(iswcntrl)
		void filter_control();
		
		/// Shorhand for defining own if-w-null function and then
		/// applying it to dropwhile_right.
		void trim_right();
		
};

/// Comparison less-then operator.
///
/// \param [in] l is left string
/// \param [in] r is right string
/// @return bool
bool operator<(PString const& l, PString const& r);

/// Concatetipn operator.
///
/// \param [in] l is left string
/// \param [in] r is right string
/// @return new string
PString operator+(PString const& l, PString const& r);

/// EQ-comaparator
///
/// \param [in] l is left string
/// \param [in] r is right string
/// @return bool
bool operator==(PString const& l, PString const& r);

/// NEQ-comaparator
///
/// \param [in] l is left string
/// \param [in] r is right string
/// @return bool
bool operator!=(PString const& l, PString const& r);

#endif
