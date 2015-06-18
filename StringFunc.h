// String-handling functions
// Copyright © 2012 The University of Chicago
#ifndef STRINGFUNC_H
#define STRINGFUNC_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include "stringsurrogate.h" 
 
class 					stringsurrogate;
typedef std::vector<string>                  stringvector;
typedef std::list<string>			stringlist;
typedef std::map<string,string>              string2string;


//template<class K, class V> class QMap;

char*    LxAlphabetizeString (const char*, int);
char*    LxAlphabetizeString (stringsurrogate);

// stringsurrogate/char/string copies
void    LxStrCpy( const stringsurrogate* From, char*& To, int Length, int Start = 0 );
void    LxStrCpy( const stringsurrogate* From, string& To, int Length, int Start = 0 );
void    LxStrCpy( const char* From, char*& To, int Length, int Start = 0 );
void    LxStrCpy( const char* From, string& To, int Length, int Start = 0 );
void    LxStrCpy( const string& From, char*& To, int Length, int Start = 0 );
void    LxStrCpy( const string& From, string& To, int Length, int Start = 0 );

void    LxStrCpy_R( const stringsurrogate* From, char*& To, int Length, int Start = 0 );
void    LxStrCpy_R( const stringsurrogate* From, string& To, int Length, int Start = 0 );
void    LxStrCpy_R( const char* From, char*& To, int Length, int Start = 0 );
void    LxStrCpy_R( const char* From, string& To, int Length, int Start = 0 );
void    LxStrCpy_R( const string& From, char*& To, int Length, int Start = 0 );
void    LxStrCpy_R( const string& From, string& To, int Length, int Start = 0 );

void    LxStrFll( const stringsurrogate* From, char*& To, int LengthFrom, int LengthTo, int Start = 0 );
void    LxStrFll( const stringsurrogate& From, char*& To, int LengthFrom, int LengthTo, int Start = 0 );
void    LxStrFll( const stringsurrogate* From, string& To, int LengthFrom, int LengthTo, int Start = 0 );
void    LxStrFll( const stringsurrogate& From, string& To, int LengthFrom, int LengthTo, int Start = 0 );
void    LxStrFll( const char* From, char*& To, int LengthFrom, int LengthTo, int Start = 0 );
void    LxStrFll( const char* From, string& To, int LengthFrom, int LengthTo, int Start = 0 );
void    LxStrFll( const string& From, char*& To, int LengthFrom, int LengthTo, int Start = 0 );
void    LxStrFll( const string& From, string& To, int LengthFrom, int LengthTo, int Start = 0 );


// stringsurrogate/char/string comparisons
int		LxStrCmp( const stringsurrogate* Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp( const stringsurrogate* Str1, const char* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp( const stringsurrogate* Str1, const string& Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp( const char* Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp( const char* Str1, const char* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp( const char* Str1, const string& Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp( const string& Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp( const string& Str1, const char* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp( const string& Str1, const string& Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );

int		LxStrCmp_R( const stringsurrogate* Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp_R( const stringsurrogate* Str1, const char* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp_R( const stringsurrogate* Str1, const string& Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp_R( const char* Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp_R( const char* Str1, const char* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp_R( const char* Str1, const string& Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp_R( const string& Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp_R( const string& Str1, const char* Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );
int		LxStrCmp_R( const string& Str1, const string& Str2, int Length1, int Length2, int Start1 = 0, int Start2 = 0 );


// stringsurrogate/char/string concatenations
void    LxStrCat( char*& Front,  const stringsurrogate* Back,     int LengthF, int LengthB,    int StartF = 0, int StartB = 0 );
void    LxStrCat( char*& Front,  const stringsurrogate& Back,     int LengthF, int LengthB,    int StartF = 0, int StartB = 0 );
void    LxStrCat( string& Front, const stringsurrogate* Back,     int LengthF, int LengthB,    int StartF = 0, int StartB = 0 );
void    LxStrCat( char*& Front,  const char* Back, int LengthF,                int LengthB,    int StartF = 0, int StartB = 0 );
void    LxStrCat( char*& Front,  const string& Back, int LengthF,              int LengthB,    int StartF = 0, int StartB = 0 );
void    LxStrCat( string& Front, const char* Back, int LengthF,                int LengthB,    int StartF = 0, int StartB = 0 );
void    LxStrCat( string& Front, const string& Back, int LengthF,              int LengthB,    int StartF = 0, int StartB = 0 );


// char/string mutators
void    LxStrLwr( char*, int, int = 0 );
void    LxStrLwr( string& );
void    LxStrUpr( char*, int, int = 0 );
void    LxStrUpr( string& );

// For RichMorphy Init test
int		OverlapOfTwoAlphabetizedLists( string, string);
int		DifferencesOfTwoAlphabetizedLists( string, string);

// conversions to string.
string IntToStringWithCommas(int n);
string DblToStringWithCommas(double n);
string Filter(string2string* filter, string s);
string DisplayInt(int n);
string DisplayFloat(float f);

// "NULL" string.
const string TheStringNULL = "NULL";

// Sorting
void    Sort_stringlist(stringlist&);
void    Sort_stringlist_FromRight(stringlist);
void    Sort_stringvector(stringlist);
void    Sort_stringvector_FromRight(stringlist);

#endif // STRINGFUNC_H
