// Implementation of stringsurrogate methods
// Copyright © 2009 The University of Chicago

#include <assert.h>
#include "stringsurrogate.h"
#include "parse.h"
#include "StringFunc.h"
#include <iostream>

typedef std::map<string,string>              string2string;


//--------------------------------------------------------------------
// Construction/Destruction
//--------------------------------------------------------------------


/**
	Constructs an empty string surrogate.
 */
stringsurrogate::stringsurrogate()
{
  m_Key = NULL;
  m_Start = 0;
  m_Length = 0;
  m_Backwards = false;
}


/**
	Constructs a string surrogate from a char array. <kbd>Key</kbd> points to the
	parent string. <kbd>StartIndex</kbd> is the index of the first character in the
	surrogate substring. <kbd>Length</kbd> is the length of the substring. Set <kbd>Backwards</kbd>
	equal to <i>TRUE</i> if all string operations should be performed in reverse.

	Examples:
		string hello_world = "Hello, world.";
		stringsurrogate s(hello_world, 3, 8, false);	// "lo, worl"
		stringsurrogate s2(hello_world, 0, 9, true);	// "ow ,olleH"

		stringsurrogate empty1(0, 0, 0, false);	// empty
		stringsurrogate empty2(0, 0, 0, true);	// empty
		stringsurrogate empty3(new char[0], 0, 0, false);	// empty, with memory leak
		stringsurrogate empty4(new char[15], 7, 0, true);	// empty, with memory leak
 */

stringsurrogate::stringsurrogate( const char* Key, const int StartIndex, const int Length, bool Backwards ):
        m_Key( Key ), m_Start( StartIndex ), m_Length( Length ), m_Backwards( Backwards )
{}

stringsurrogate::stringsurrogate(const char* s, int len)
	: m_Key(s), m_Start(0), m_Length(len), m_Backwards(false)
{ assert(s != 0 && len >= 0); }

/**
	Constructs a string surrogate from a parse. <kbd>Parse</kbd> is a reference to the
	parent string. <kbd>StartIndex</kbd> is the index of the first character in the
	surrogate substring. <kbd>Length</kbd> is the length of the substring. If <kbd>Length</kbd> = -1, 
	the substring will continue to the end of the parent string. Set <kbd>Backwards</kbd>
	equal to <i>TRUE</i> if all string operations should be performed in reverse.
 */

stringsurrogate::stringsurrogate( const parse& Parse, const int StartIndex, const int Length, bool Backwards )
{
  m_Key = Parse.GetKeyPointer();
  m_Start = StartIndex;
  if( Length < 0 ) m_Length = Parse.GetKeyLength() - StartIndex;
  else m_Length = Length;
  m_Backwards = Backwards;
}


/**
	Constructs a string surrogate from a pointer to a parse. <kbd>pParse</kbd> is a pointer to the
	parent string. <kbd>StartIndex</kbd> is the index of the first character in the
	surrogate substring. <kbd>Length</kbd> is the length of the substring. If <kbd>Length</kbd> = -1, 
	the substring will continue to the end of the parent string. Set <kbd>Backwards</kbd>
	equal to <i>TRUE</i> if all string operations should be performed in reverse.
 */

stringsurrogate::stringsurrogate( const parse* pParse, const int StartIndex, const int Length, bool Backwards  )
{
  m_Key = pParse->GetKeyPointer();
  m_Start = StartIndex;
  if( Length < 0 ) m_Length = pParse->GetKeyLength() - StartIndex;
  else m_Length = Length;
  m_Backwards = Backwards;
}

/**
	Constructs a string surrogate from a string. <kbd>String</kbd> is a pointer to the
	parent string. <kbd>Start</kbd> is the index of the first character in the
	surrogate substring. <kbd>Length</kbd> is the length of the substring. If <kbd>Length</kbd> = -1, 
	the substring will continue to the end of the parent string. Set <kbd>Backwards</kbd>
	equal to <i>TRUE</i> if all string operations should be performed in reverse.

	Note: Use carefully! If the string is changed, the char* of the string may be in a new location
	and this surrogate will not point to the right memory location anymore.

	2012: This looks like a bad idea. We need to rethink who owns the memory, and who knows it.
 */


stringsurrogate::stringsurrogate( const string String, const int Start, const int Length, bool Backwards )
{
  //m_Key = String.unicode();
  m_Key = String.c_str();
  m_Start = Start;
  if( Length < 0 ) m_Length = String.length();
  else m_Length = Length;
  m_Backwards = Backwards;
}


/**
	Copies another string surrogate. <kbd>other</kbd> is the string surrogate to be copied.
 */

stringsurrogate::stringsurrogate( const stringsurrogate& other )
{
  m_Key = other.GetKey();
  m_Start = other.GetStart();
  m_Length = other.GetLength();
  m_Backwards = other.IsBackwards();
}


/**
	Destroys this string surrogate. Because surrogates do not own any string
	data, this destructor does nothing.
 */

stringsurrogate::~stringsurrogate()
{}


//--------------------------------------------------------------------
// Overloaded Operators
//--------------------------------------------------------------------

// Gets the nth char from the string surrogate.
//
// Paramaters:
//		- n - the desired index
//
// Returns:
//		- char - the nth char in m_Key after m_Start, NULL if n is too large or too small
//
/**
	Returns the the nth char from the string surrogate. <kbd>n</kbd> is the index
	of the desired character in the surrogate.
 */

char stringsurrogate::operator[] (const int n ) const
{
  return GetChar(n);
}


// Sets the string surrogate equal to the key in a parse.
//
// Parameters:
//		- Parse - contains a char array called 'm_Key'
//
/**
	Makes a string surrogate from a parse. <kbd>Parse</kbd> is the parent parse.
 */
void stringsurrogate::operator= ( const parse& Parse )
{
  m_Key = Parse.GetKeyPointer();
  m_Start = 0;
  m_Length = Parse.GetKeyLength();
  m_Backwards = false;
}


// Copies another string surrogate.
//
// Parameters:
//		- const stringsurrogate - to be copied
//
/**
	Makes a copy of another string surrogate. <kbd>other</kbd> is the surrogate 
	that will be copied.
 */
 
void stringsurrogate::operator= ( const stringsurrogate  other )  
{
  m_Key = other.GetKey();
  m_Start = other.GetStart();
  m_Length = other.GetLength();
  m_Backwards = other.IsBackwards();
}
 

// Sets the string surrogate equal to the unicode char array
// of a string.
//
// Note: Use carefully! If the string is changed the
// char* of the string may be in a new location and this
// surrogate will not point to the right memory location
// anymore.
//
// Parameters:
//		- String - contains a char array called 'unicode'
//
/**
	Makes a surrogate of a string. <kbd>String</kbd> is the parent
	string.

	Note: Use carefully! If the string is changed the char* of the 
	string may be in a new location and this surrogate will not
	represent the same string.
 */

void stringsurrogate::operator= ( const string String )
{
  m_Key = String.c_str();
  m_Start = 0;
  m_Length = String.length();
  m_Backwards = false;
}


// Sets the string surrogate equal to the key in a parse*
//
// Parameters:
//		- Parse - contains a char array called 'm_Key'
//
/**
	Makes a string surrogate of a pointer to a parse. <kbd>pParse</kbd>
	pointer to the parent parse.
 */
void stringsurrogate::operator= ( const parse* pParse )
{ operator= ( *pParse ); }


// Checks if this string surrogate does not have the same characters
// as another string surrogate.
//
// Parameters:
//		- SS - the other string surrogate
//
// Returns:
//		- bool - true if any char in SS does not match the corresponding char in the string surrogate from m_Start to m_Start + m_Length
//
/**
	Checks if this string surrogate does not have the same characters
	as another string surrogate. <kbd>SS</kbd> is the other surrogate
	to compare.
 */

bool stringsurrogate::operator!= ( const stringsurrogate& SS ) const
{ return !operator== (SS); }


// Checks if this string surrogate does not have the same characters
// as a parse.
//
// Parameters:
//		- Parse - parse has a member m_Key which is an array of type char
//
// Returns:
//		- bool - true if any char in Parse.m_Key does not match the corresponding char in the string surrogate from m_Start to m_Start + m_Length
// 
/**
	Checks if this string surrogate does not have the same characters
	as a parse. <kbd>Parse</kbd> is the parse to compare.
 */

bool stringsurrogate::operator!= ( const parse& Parse ) const
{ return !operator== (Parse); }


// Combines this string surrogate and another into a parse.
// No change is made to this surrogate or the other.
//
// Parameters:
//		- ssRight - the surrogate that will be appended
//
// Returns:
//		- parse - a copy of this surrogate plus ssRight
//

/**
	Combines this string surrogate and another into
	a parse. No change is made to either string surrogate.
	<kbd>ssRight</kbd> is the surrogate to the right of the operator.
 */

parse  stringsurrogate::operator+ ( const stringsurrogate& ssRight ) const
{
  parse parse ( *this );
  parse.Append (ssRight);
  return parse;
}


// Combines this string surrogate and a char into a parse,
// no change is made to this surrogate.
//
// Parameters:
//		- c - the char that will be appended
//
// Returns:
//		- parse - a copy of this surrogate plus c
//
/**
	Combines this string surrogate and a single char into a parse. No
	change is made to this surrogate. <kbd>c</kbd> is the character to the
	right of the operator.
 */

parse  stringsurrogate::operator+ ( const char c ) const
{
  parse parse (*this);
  parse.Append (c);
  return parse;
}


// Checks if this string surrogate has the same characters
// as another string surrogate.
//
// Parameters:
//		- SS - the other string surrogate
//
// Returns:
//		- bool - true if every char in SS matches every char in the string surrogate from m_Start to m_Start + m_Length
//
/**
	Compare the characters of this string surrogate with those of
	another surrogate. <kbd>SS</kbd> is the other surrogate (to the
	right of the operator).
 */

bool stringsurrogate::operator== ( const stringsurrogate& SS ) const
{
  if ( SS.GetLength() != m_Length ) return false;

  for ( int i=0; i<m_Length; i++ )
  {
    if ( GetChar(i) != SS[i] )
    {
      return false;
    }
  }
  return true;
}


// Checks if this string surrogate has the same characters
// as a parse.
//
// Parameters:
//		- Parse - parse has a member m_Key which is an array of type char
//
// Returns:
//		- bool - true if every char in Parse.m_Key matches every char in the string surrogate from m_Start to m_Start + m_Length
//

/**
	Compares the characters of this surrogate with the characters
	of a parse. <kbd>Parse</kbd> is the parse to compare with.
 */

bool stringsurrogate::operator== ( const parse& Parse ) const
{
  stringsurrogate SS = Parse.GetKey();
  return (*this) == SS;
}

// Checks if this string surrogate is alphabetically
// greater than another string surrogate.
//
// Parameters:
//		- SS - the other string surrogate
//
// Returns:
//		- bool - true if this surrogate is alphabetically greater than SS, this includes when they are equal from m_Start through m_Start + m_Length and this surrogate is shorter than SS
//

/**
	Compares the alphabetical value of this string surrogate with
	another, returns TRUE if this is greater. <kbd>SS</kbd> is the 
	other string surrogate (on the right side of the operator).
 */

bool stringsurrogate::operator> ( const stringsurrogate& SS ) const
{
  int length = m_Length;
  if( length > SS.GetLength() ) length = SS.GetLength();

  for ( int i=0; i<length; i++ )
  {
    if ( GetChar(i) < SS[i] ) return false;
    else if( GetChar(i) > SS[i] ) return true;
  }
  if( m_Length <= SS.GetLength() ) return false;
  else return true;
}


// Checks if this string surrogate is alphabetically
// less than another string surrogate.
//
// Parameters:
//		- SS - the other string surrogate
//
// Returns:
//		- bool - true if this surrogate is alphabetically less than SS, this includes when they are equal from m_Start through m_Start + m_Length and this surrogate is longer than SS
//

/**
	Compares the alphabetical value of this string surrogate with 
	another, returns TRUE if this is the lesser. <kbd>SS</kbd> is the
	other string surrogate (on the right side of the operator).
 */

bool stringsurrogate::operator<  ( const stringsurrogate& SS ) const
{
  int length = m_Length;
  if( length > SS.GetLength() ) length = SS.GetLength();

  for ( int i=0; i<length; i++ )
  {
    if ( GetChar(i) > SS[i] ) return false;
    else if( GetChar(i) < SS[i] ) return true;
  }
  if( m_Length < SS.GetLength() ) return true;
  else return false;
}


//-----------------------------------------------------------------
// Other Methods
//-----------------------------------------------------------------


// Returns the parent string key.
//
/**
	Returns a pointer to the parent's char string.
 */
const char* stringsurrogate::GetKey() const
{ return m_Key; }

// Returns the length of the substring.
//
/** 
	Returns the length of the surrogate.
 */
int stringsurrogate::GetLength() const
{ return m_Length; }

// Returns the start position of the substring.
//
/**
	Returns the start position of the surrogate relative
	to the beginning of the parent string.
 */
int stringsurrogate::GetStart() const
{ return m_Start; }

// Finds out if the substring is backwards.
//
/**
	Returns the state of the Backwards flag.
 */
bool stringsurrogate::IsBackwards() const
{ return m_Backwards; }

 // Designates the surrogate as a backwards substring.
 //
/**
	Sets the <i>Backwards</i> state of the surrogate.
 */
void stringsurrogate::SetBackwards( bool b )
{ m_Backwards = b; }

// Gets the nth char from the string surrogate.
//
// Paramaters:
//		- n - the desired index
//
// Returns:
//		- char - the nth char in m_Key after m_Start, NULL if n is too large or too small
//
/**
	Gets the nth char from the string surrogate. <kbd>n</kbd> is the
	index of the desired character. Returns <i>NULL</i> if n is out of
	range.
 */

char stringsurrogate::GetChar( const int n ) const
{
	if ( n >= 0 && n < (int)m_Length )
	{
		if ( m_Backwards )
			return m_Key[ m_Start + m_Length - n - 1 ];
		else
			return m_Key[ m_Start + n ];
	} else
		return char(0);
}

// Finds out if this string surrogate is a single punctuation mark.
//
// Returns:
//		- bool - true if string surrogate is one character and that character is a punctuation
//
/**
	Checks if this surrogate is a single punctuation mark.
 */
/*
bool stringsurrogate::IsPunctuation( string punctuation ) const
{
   if( punctuation == "EMPTY" ) punctuation = "";

   if ( m_Length == 1)
   {
    return ( punctuation.find( m_Key[ m_Start ] ) > -1 || m_Key[m_Start].isPunct() );
   }
   return false;
}
*/

// Makes another surrogate of the left n chars in this surrogate.
//
// Parameters:
//		- n - number of desired chars
//
// Returns:
//		- stringsurrogate - a different surrogate with just the left n chars; the new surrogate points to the same char array but has different m_Start and m_Length values
//
/**
	Makes another surrogate of the left n chars in this surrogate. <kbd>n</kbd>
	is the length of the new surrogate.
 */

stringsurrogate stringsurrogate::Left (int n) const
{
  if( n >= 0 )
  {
    if( n <= (int)m_Length )
    {
      if( m_Backwards )
        return stringsurrogate( m_Key, m_Start+m_Length-n, n, m_Backwards );
      else
        return stringsurrogate( m_Key, m_Start, n, m_Backwards );
    }
    else
      return stringsurrogate( m_Key, m_Start, m_Length, m_Backwards );
  }
  else
    return stringsurrogate();
}


// Makes another surrogate of the right n chars in this
// surrogate.
//
// Parameters:
//		- n - number of desired chars
//
// Returns:
//		- stringsurrogate - a different surrogate with just the right n chars; the new surrogate points to the same char array but has different m_Start and m_Length values
//
/**
	Makes another surrogate of the right n chars in this surrogate. <kbd>n</kbd>
	is the length of the new surrogate.
 */

stringsurrogate stringsurrogate::Right (int n) const
{
  if( n >= 0 )
  {
    if( n <= (int)m_Length )
    {
      if( m_Backwards )
        return stringsurrogate( m_Key, m_Start, n, m_Backwards );
      else
        return stringsurrogate( m_Key, m_Start+m_Length-n, n, m_Backwards );
    }
    else
      return stringsurrogate( m_Key, m_Start, m_Length, m_Backwards );
  }
  else
    return stringsurrogate();
}

// Makes another surrogate of the middle SpanLength chars
// in this surrogate, starting at character SkipHowMany.
//
// Parameters:
//		- SkipHowMany - starting index, also number of chars skipped SpanLength - the number of characters to include, if negative or too large, the remainder of the string following SkipHowMany will be returned, default = -1
//
// Returns:
//		- stringsurrogate - a different surrogate made from the same char array with m_Start at SkipHowMany plus this.m_Start and m_Length = SpanLength
//
/** 
	Makes another surrogate of chars from the middle of this surrogate. <kbd>SkipHowMany</kbd> is the
	starting position of the new sub-string. <kbd>SpanLength</kbd> is the length of the sub-string.
 */

stringsurrogate stringsurrogate::Mid ( int SkipHowMany, int SpanLength ) const
{
  if ( SpanLength < 0  || SkipHowMany + SpanLength > (int)m_Length )
  {
    // Readjust SpanLength to be the remainder
    // of this surrogate
    SpanLength = m_Length - SkipHowMany;
  }

  if ( SkipHowMany >= 0 && SkipHowMany < (int)m_Length )
    if( m_Backwards ) return stringsurrogate( m_Key, m_Start+m_Length-SkipHowMany-SpanLength, SpanLength, m_Backwards );
    else return stringsurrogate ( m_Key, m_Start+SkipHowMany, SpanLength, m_Backwards );

  else return stringsurrogate();
}

// Returns a copy of the first character in the surrogate.
//
// Returns:
//		- char - the character at m_Key[m_Start]
//
/**
	Returns a copy of the first character in the surrogate.
 */

char stringsurrogate::FirstChar() const
{
  return GetChar(m_Start);
}


// Returns a copy of the last character in the surrogate.
//
// Returns:
//		- char - the character at m_Key[m_Start+m_Length-1]
//
/**
	Returns a copy of the last character in the surrogate.
 */

char stringsurrogate::LastChar() const
{
  return GetChar(m_Start + m_Length-1);
}


// Returns a string copy of the surrogate.
//
// Returns:
//		- string - a real string copy of the surrogate
//
/** 
        Makes a string copy of the surrogate for displaying and
 	printing. <kbd>filter</kbd> is a map of individual characters
	to strings of multiple characters that will replace them
	in the output.
 */

string stringsurrogate::Display() const
{
  //cout << "\nStringSurrogate line 667 Display function";
  string this_string = "";
  for ( int i=m_Start; i<m_Start + m_Length; i++ )
  {
    this_string += GetChar(i);
  }

  //if( filter ) return Filter( filter, string );
  //else
  //cout << endl << "StringSurrogate line 676:" << this_string << " End of string surrogate display.";
  return this_string;
}


// Makes the string surrogate empty (NULL).
//
/**
	Makes the string surrogate empty (NULL).
 */

void stringsurrogate::MakeNull() {
  m_Key = NULL;
  m_Start = 0;
  m_Length = 0;
  m_Backwards = false;
}


// Converts a surrogate that has only the characters "NULL"
// into an empty (NULL) string surrogate.
//
/**
	Converts this surrogate into into an empty surrogate if it
	only has the characters "NULL".
 */

void stringsurrogate::ConvertNULL()
{
  if ( IsNULL() )  MakeNull();
}


// Finds out if the surrogate has only the characters "NULL".
//
// Returns:
//		- bool - true if the surrogate's length is 4 and it is equal to "NULL"
//

/**
	Finds out if this surrogate only has the characters "NULL".
 */

bool stringsurrogate::IsNULL() const
{
  string Null = "NULL";
  if ( m_Length == 4 && operator== ( stringsurrogate(Null) ) )
  {
    return true;
  }
  return false;
}
