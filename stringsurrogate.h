// Pointer to a substring of a parse or string
// Copyright © 2009 The University of Chicago
#ifndef STRINGSURROGATE_H
#define STRINGSURROGATE_H

#include <string>
#include <wchar.h>
using std::string;

class parse;

/// A surrogate for passing substrings.
/** 
	In Linguistica, substrings are often passed as parameters that will never be edited. 
	To minimize	unnecessary string copying, we use the string surrogate to represent strings. 
	String surrogates are the pair (<i>s</i>,<i>l</i>), where <i>s</i> is a pointer to the 
	beginning of the string and <i>l</i> is the length of the string.

	In certain cases, the reverse string is desired. String surrogates have a <i>backwards</i>
	flag. When the flag is set to <i>true</i>, all operations on the string surrogate will
	iterate from the end of the surrogate to the beginning.
 */

class stringsurrogate
{
protected:
        const char*  m_Key;			///< pointer to parent string
        int             m_Start;		///< start position of substring in parent string
        int             m_Length;		///< length of substring
        bool            m_Backwards;	///< true if string operations should iterate in reverse


public:
	// construction/destruction.

        stringsurrogate();
	/// requires: len >= 0
        stringsurrogate(const char* s, int len);
	/// requires: len >= 0
        stringsurrogate(const char* s, int pos, int len,
			bool reversed = false);
        stringsurrogate(const parse& s, int pos = 0, int len = -1,
			bool reversed = false);
        stringsurrogate(string s, int pos = 0, int len = -1,
			bool reversed = false);
	/// deprecated
        stringsurrogate(const parse* s, int pos = 0, int len = -1,
			bool reversed = false);
        virtual ~stringsurrogate();

	// copy.

        stringsurrogate(const stringsurrogate& other);
	void   operator=  ( const parse& );
	void   operator=  ( const parse* pParse );
	void   operator=  ( const string );
	//        void   operator=  ( const stringsurrogate& );
        void   operator=   ( const stringsurrogate   )   ;

	// Operators
	char  operator[] ( const int ) const;
        parse operator+  ( const stringsurrogate& ) const;
	parse operator+  ( const char ) const;
        bool   operator== ( const stringsurrogate& ) const;
	bool   operator== ( const parse& ) const;
        bool   operator!= ( const stringsurrogate& SS ) const;
	bool   operator!= ( const parse& Parse ) const;
        bool   operator>  ( const stringsurrogate& ) const;
        bool   operator<  ( const stringsurrogate& ) const;

	// Accessors
        string              	Display(  ) const;
        //string            	Display( QMap<string, string>* filter = NULL ) const;
        char 			FirstChar() const;
        const char*      	GetKey() const;
        int                 	GetLength() const;
        int                 	GetStart() const;
        bool                	IsBackwards() const;
        bool                	IsNULL() const;
        bool                	IsPunctuation( string ) const;
        char             	LastChar() const;
        stringsurrogate     	Left( int ) const;
        stringsurrogate     	Mid( int SkipHowMany, int SpanLength = -1 ) const;
        stringsurrogate     	Right( int ) const;

	// Mutators
	void ConvertNULL();
	void MakeNull();
	void SetBackwards( bool b = true );

private:
	// Accessors
	char GetChar( const int ) const;
};

#endif // STRINGSURROGATE_H
