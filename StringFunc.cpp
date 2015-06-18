// Implementation of string-handling functions
// Copyright © 2009 The University of Chicago
#include "StringFunc.h"

#include <string>

#include <algorithm>

#include <sstream> // to convert numbers to strings
#include <cassert>
#include "stringsurrogate.h"

//using namespace std;

//typedef map<string,string>              string2string;
//typedef vector<string>                  stringvector;
 

char* LxAlphabetizeString (const char* this_string, int length)
{
  int i;
  int*  Rank = new int [ length ];
  // Rank is an array that keeps track, for each letter occurrence, how many letters in the word are strictly
  // earlier than it alphabetically.
  for ( i =0; i < length; i++)
  {
    int p = 0;
    for (int j = 0; j < length; j++)
    {
      if ( this_string[j] < this_string[i] )
        p++;
    }
    Rank[i] = p;
  }

  char* NewString = new char [ length + 1];

  for ( i = 0; i<= length; i++)
    NewString[i] = '\0';

  int p = 0;
  for ( i = 0; i < length; i++)
  {
    p = Rank[  i  ];
    while ( NewString[p] != '\0' )
      p++;
    NewString[p] = this_string[i];
  }

  delete [] Rank;

  return NewString;

}
char* LxAlphabetizeString (stringsurrogate mystring){
	return LxAlphabetizeString ( mystring.GetKey(), mystring.GetLength());
}

//--------------------------------------------------------------------
// stringsurrogate/char/string copies
//--------------------------------------------------------------------

void    LxStrCpy( const stringsurrogate* From, char*& To, int Length, int Start )
{
  delete [] To;
  To = new char[Length];

  for( int i=0; i<Length; i++ )
  {
    To[i] = (*From)[i+Start];
  }
}
 

void    LxStrCpy( const stringsurrogate* From, string& To, int Length, int Start )
{
  To = "";
  for( int i=0; i<Length; i++ )
  {
    To += (*From)[i+Start];
  }
}


void    LxStrCpy( const char* From, char*& To, int Length, int Start )
{
  delete [] To;
  To = new char[Length];

  for ( int i=0; i<Length; i++ )
  {
    To[i] = From[i+Start];
  }
}


void    LxStrCpy( const char* From, string& To, int Length, int Start )
{
  To = "";
  for ( int i=0; i<Length; i++ )
  {
    To += From[i+Start];
  }
}


void    LxStrCpy( const string& From, char*& To, int Length, int Start )
{
  delete [] To;
  To = new char[Length];

  for ( int i=0; i<Length; i++ )
  {
    To[i] = From[i+Start];
  }
}


void    LxStrCpy( const string& From, string& To, int Length, int Start )
{
  //To = From.mid( Start, Length );
  To = From.substr( Start, Length);
}


void    LxStrCpy_R( const stringsurrogate* From, char*& To, int Length, int Start )
{
  delete [] To;
  To = new char[Length];

  for ( int i=0; i<Length; i++ )
  {
    To[i] = (*From)[Length+Start-i-1];
  }
}


void    LxStrCpy_R( const stringsurrogate* From, string& To, int Length, int Start )
{
  for ( int i=0; i<Length; i++ )
  {
    To += (*From)[Length+Start-i-1];
  }
}


void    LxStrCpy_R( const char* From, char*& To, int Length, int Start )
{
  delete [] To;
  To = new char[Length];

  for ( int i=0; i<Length; i++ )
  {
    To[i] = From[Length+Start-i-1];
  }
}


void    LxStrCpy_R( const char* From, string& To, int Length, int Start )
{
  for ( int i=0; i<Length; i++ )
  {
    To += From[Length+Start-i-1];
  }
}


void    LxStrCpy_R( const string& From, char*& To, int Length, int Start )
{
  delete [] To;
  To = new char[Length];

  for ( int i=0; i<Length; i++ )
  {
    To[i] = From[Length+Start-i-1];
  }
}


void    LxStrCpy_R( const string& From, string& To, int Length, int Start )
{
  for ( int i=0; i<Length; i++ )
  {
    To[i] = From.at(Length+Start-i-1);
  }
}

                                                                                                           
void    LxStrFll( const stringsurrogate* From, char*& To, int LengthFrom, int LengthTo, int Start )
{
  int Length = LengthFrom;
  if( Length > LengthTo ) Length = LengthTo;

  for ( int i=0; i<Length; i++ )
  {
    To[i] = (*From)[i+Start];
  }
}

void    LxStrFll( const stringsurrogate& From, char*& To, int LengthFrom, int LengthTo, int Start )
{
  int Length = LengthFrom;
  if( Length > LengthTo ) Length = LengthTo;

  for ( int i=0; i<Length; i++ )
  {
    To[i] = (From)[i+Start];
  }
}


void    LxStrFll( const stringsurrogate* From, string& To, int LengthFrom, int LengthTo, int Start )
{
  int Length = LengthFrom;
  if( Length > LengthTo ) Length = LengthTo;

  for ( int i=0; i<Length; i++ )
  {
    To[i] = (*From)[i+Start];
  }
}
 
void    LxStrFll( const char* From, char*& To, int LengthFrom, int LengthTo, int Start )
{
  int Length = LengthFrom;
  if( Length > LengthTo ) Length = LengthTo;

  for ( int i=0; i<Length; i++ )
  {
    To[i] = From[i+Start];
  }
}


void    LxStrFll( const char* From, string& To, int LengthFrom, int LengthTo, int Start )
{
  int Length = LengthFrom;
  if( Length > LengthTo ) Length = LengthTo;

  for ( int i=0; i<Length; i++ )
  {
    To[i] = From[i+Start];
  }
}


void    LxStrFll( const string& From, char*& To, int LengthFrom, int LengthTo, int Start )
{
  int Length = LengthFrom;
  if( Length > LengthTo ) Length = LengthTo;

  for ( int i=0; i<Length; i++ )
  {
    To[i] = From[i+Start];
  }
}


void    LxStrFll( const string& From, string& To, int LengthFrom, int LengthTo, int Start )
{
  int Length = LengthFrom;
  if( Length > LengthTo ) Length = LengthTo;

  for ( int i=0; i<Length; i++ )
  {
    To[i] = From[i+Start];
  }
}          


//--------------------------------------------------------------------
// stringsurrogate/char/string comparisonsmid
//--------------------------------------------------------------------


int      LxStrCmp( const stringsurrogate* Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=0; i<length; i++ )
  {
    if ( (*Str1)[Start1+i] > (*Str2)[Start2+i] ) return 1;
    if ( (*Str1)[Start1+i] < (*Str2)[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp( const stringsurrogate* Str1, const char* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=0; i<length; i++ )
  {
    if ( (*Str1)[Start1+i] > Str2[Start2+i] ) return 1;
    if ( (*Str1)[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp( const stringsurrogate* Str1, const string& Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=0; i<length; i++ )
  {
    if ( (*Str1)[Start1+i] > Str2[Start2+i] ) return 1;
    if ( (*Str1)[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp( const char* Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=0; i<length; i++ )
  {
    if ( Str1[Start1+i] > (*Str2)[Start2+i] ) return 1;
    if ( Str1[Start1+i] < (*Str2)[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp( const char* Str1, const char* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=0; i<length; i++ )
  {
    if ( Str1[Start1+i] > Str2[Start2+i] ) return 1;
    if ( Str1[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp( const char* Str1, const string& Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=0; i<length; i++ )
  {
    if ( Str1[Start1+i] > Str2[Start2+i] ) return 1;
    if ( Str1[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp( const string& Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=0; i<length; i++ )
  {
    if ( Str1[Start1+i] > (*Str2)[Start2+i] ) return 1;
    if ( Str1[Start1+i] < (*Str2)[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp( const string& Str1, const char* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=0; i<length; i++ )
  {
    if ( Str1[Start1+i] > Str2[Start2+i] ) return 1;
    if ( Str1[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp( const string& Str1, const string& Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=0; i<length; i++ )
  {
    if ( Str1[Start1+i] > Str2[Start2+i] ) return 1;
    if ( Str1[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp_R( const stringsurrogate* Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=length-1; i>=0; i-- )
  {
    if ( (*Str1)[Start1+i] > (*Str2)[Start2+i] ) return 1;
    if ( (*Str1)[Start1+i] < (*Str2)[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp_R( const stringsurrogate* Str1, const char* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=length-1; i>=0; i-- )
  {
    if ( (*Str1)[Start1+i] > Str2[Start2+i] ) return 1;
    if ( (*Str1)[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp_R( const stringsurrogate* Str1, const string& Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=length-1; i>=0; i-- )
  {
    if ( (*Str1)[Start1+i] > Str2[Start2+i] ) return 1;
    if ( (*Str1)[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp_R( const char* Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=length-1; i>=0; i-- )
  {
    if ( Str1[Start1+i] > (*Str2)[Start2+i] ) return 1;
    if ( Str1[Start1+i] < (*Str2)[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp_R( const char* Str1, const char* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=length-1; i>=0; i-- )
  {
    if ( Str1[Start1+i] > Str2[Start2+i] ) return 1;
    if ( Str1[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp_R( const char* Str1, const string& Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=length-1; i>=0; i-- )
  {
    if ( Str1[Start1+i] > Str2[Start2+i] ) return 1;
    if ( Str1[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp_R( const string& Str1, const stringsurrogate* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=length-1; i>=0; i-- )
  {
    if ( Str1[Start1+i] > (*Str2)[Start2+i] ) return 1;
    if ( Str1[Start1+i] < (*Str2)[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp_R( const string& Str1, const char* Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=length-1; i>=0; i-- )
  {
    if ( Str1[Start1+i] > Str2[Start2+i] ) return 1;
    if ( Str1[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}


int      LxStrCmp_R( const string& Str1, const string& Str2, int Length1, int Length2, int Start1, int Start2 )
{
  assert( Length1 >= 0 && Length2 >= 0 );
  int length = Length1;
  if( Length1 > Length2 ) length = Length2;

  for ( int i=length-1; i>=0; i-- )
  {
    if ( Str1[Start1+i] > Str2[Start2+i] ) return 1;
    if ( Str1[Start1+i] < Str2[Start2+i] ) return -1;
  }
  if ( Length1 > Length2 ) return 1;
  if ( Length1 < Length2 ) return -1;
  return 0;
}



//--------------------------------------------------------------------
// stringsurrogate/char/string concatenations
//--------------------------------------------------------------------

void    LxStrCat( char*& Front, const stringsurrogate* Back, int LengthF, int LengthB, int StartF, int StartB )
{
  int length = LengthF + LengthB,
    i;
  char* NewQChar = new char[ length ];
  for(  i=0; i<LengthF; i++ )
  {
    NewQChar[i] = Front[StartF+i];
  }
  for( i=0; i<LengthB; i++ )
  {
    NewQChar[LengthF+i] = (*Back)[StartB+i];
  }
  delete [] Front;
  Front = NewQChar;
}
void    LxStrCat( char*& Front, const stringsurrogate& Back, int LengthF, int LengthB, int StartF, int StartB )
{
  int length = LengthF + LengthB,
    i;
  char* NewQChar = new char[ length ];
  for(  i=0; i<LengthF; i++ )
  {
    NewQChar[i] = Front[StartF+i];
  }
  for( i=0; i<LengthB; i++ )
  {
    NewQChar[LengthF+i] = Back[StartB+i];
  }
  delete [] Front;
  Front = NewQChar;
}


void    LxStrCat( char*& Front, const char* Back, int LengthF, int LengthB, int StartF, int StartB )
{
  int length = LengthF + LengthB,
    i;
  char* NewQChar = new char[ length ];
  for(  i=0; i<LengthF; i++ )
  {
    NewQChar[i] = Front[StartF+i];
  }
  for( i=0; i<LengthB; i++ )
  {
    NewQChar[LengthF+i] = Back[StartB+i];
  }
  delete [] Front;
  Front = NewQChar;
}

void    LxStrCat( char*& Front, const string& Back, int LengthF, int LengthB, int StartF, int StartB )
{
  int length = LengthF + LengthB,
    i;
  char* NewQChar = new char[ length ];
  for( i=0; i<LengthF; i++ )
  {
    NewQChar[i] = Front[StartF+i];
  }
  for( i=0; i<LengthB; i++ )
  {
    NewQChar[LengthF+i] = Back[StartB+i];
  }
  delete [] Front;
  Front = NewQChar;
}


void    LxStrCat( string& Front, const stringsurrogate* Back, int LengthF, int LengthB, int StartF, int StartB )
{
  //Front = Front.mid( StartF, LengthF );
  Front = Front.substr( StartF, LengthF );
  for( int i=0; i<LengthB; i++ )
  {
    Front += (*Back)[StartB+i];
  }
}


void    LxStrCat( string& Front, const char* Back, int LengthF, int LengthB, int StartF, int StartB )
{
  Front = Front.substr( StartF, LengthF );
  for( int i=0; i<LengthB; i++ )
  {
    Front += Back[StartB+i];
  }
}
/*
void    LxStrCat( string& Front, const string& Back, int LengthF, int LengthB, int StartF, int StartB )
{
  Front = Front.substr( StartF, LengthF ) + Back.substr( StartB, LengthB );
}
*/



//--------------------------------------------------------------------
// char/string mutators
//--------------------------------------------------------------------


void    LxStrLwr( char* str, int Length, int Start )
{
  for( int i=Start; i<Length; i++ )
  {
    str[i] =towlower( str[i] );
  }
}

/*
void    LxStrLwr( string& str )
{
  str = str.towlower();
}
*/
void    LxStrUpr( char* str, int Length, int Start )
{
  for( int i=Start; i<Length; i++ )
  {
    str[i] = toupper( str[i] );
  }
}

/*
void    LxStrUpr( string& str )
{
  str = str.toupper();
}
*/

/// For Rich Morphy Init Test
int		OverlapOfTwoAlphabetizedLists( string str1, string str2)
{
	int		Count = 0;
	int		i = 0, j= 0;
        char	str1c, str2c;

	while (i <= (int)str1.length() && j <= (int) str2.length()  )
	{
		str1c = str1[i]; 
		str2c = str2[j]; 
		if (str1c == str2c )
		{
			Count++;
			i++; j++; continue;
		}
		if (str1c < str2c )
		{
			i++;
			continue;
		}
		if (str1c > str2c )
		{
			j++;
			continue;
		}		
	}
	return Count;


}
int		DifferencesOfTwoAlphabetizedLists( string str1, string str2)
{

	int Count = 0;
	int i = 0, j= 0;
        char str1c, str2c;

	while (i <= (int) str1.length() || j <= (int) str2.length()  )
	{
		if ( i >= static_cast <int> ( str1.length() ) ) 
		{
			if ( j >= static_cast <int> (str2.length()) ) break;

			Count++;
			j++;
			continue;
		}
		if ( j >= static_cast <int> (str2.length()) ) 
		{
			if ( i >= static_cast <int> (str1.length()) ) break;

			Count++;
			i++;
			continue;
		}

		str1c = str1[i]; 
		str2c = str2[j]; 

		if (str1c == str2c )
		{			
			i++; j++; continue;
		}
		if (str1c < str2c )
		{
			i++;
			Count++;
			continue;
		}
		if (str1c > str2c )
		{
			j++;
			Count++;
			continue;
		}		
	}
	return Count;

}

// conversions to string.
/*
string IntToStringWithCommas( int n )
{
  //string Number, comma = ",", WithCommas = "";
  //Number = string("%1").arg(n).stripWhiteSpace();

  string Number;
  string comma = ",";
  string WithCommas = "";
  ostringstream oss;
  oss << n;
  Number = oss.str();

  int commacount = (Number.length()-1)/3;
  for( int i=1; i<=commacount; i++ )
  {
   // WithCommas = comma + Number.right( 3 ) + WithCommas;
    //Number = Number.left( Number.length() - 3 );

    WithCommas = comma + Number.substr( Number.length() - 3, 3 ) + WithCommas;
    Number = Number.substr(0,Number.length() - 3 );

  }
  return Number + WithCommas;
}

string DblToStringWithCommas( double d )
{
 //number = string("%1").arg( d, 0, 'f', 3 ).stripWhiteSpace();


  string number, decimals, comma = ",", withCommas = "";
  ostringstream oss;
  oss << d;
  number = oss.str(); 

  int pointLoc = number.find('.');

  //decimals = number.mid( pointLoc );
  //number = number.left( pointLoc );

  decimals = number.substr( pointLoc, number.length()- pointLoc);
  number = number.substr(0, pointLoc );
  int commacount = (pointLoc-1)/3;
  for( int i=1; i<=commacount; i++ )
  {
    //withCommas = comma + number.right( 3 ) + withCommas;
    //number = number.left( number.length() - 3 );

    withCommas = comma + number.substr( number.length() - 3, 3) + withCommas;    
    number = number.substr(0, number.length() - 3 );
  }
  return number + withCommas + decimals;
}
*/
string lxa_replace (string basestring, string a, string  b)
{
    int startpos = 0;
    while (int pos = basestring.find(a, startpos) ){
        basestring.replace(pos, a.length(), b);
    }
    return basestring;
}


string Filter(string2string* filter, string this_string)
{

  // Find the length of longest filter string
  uint longest = 0;
  for (string2string::const_iterator it = filter->begin(); it != filter->end(); ++it)
      if (longest < it->first.length() )
                longest = it->first.length();

  // Filter from longest to shortest

  for( uint i = longest; i >= 0; i-- )
  {
      for (string2string::const_iterator it = filter->begin(); it != filter->end(); ++it){
        if (it->first.length() == i)
                //filtered.replace(it->first, it->second);
                this_string = lxa_replace (this_string, it->first, it->second);
        }
  }
  return this_string;
}
/*
string DisplayInt ( int n )
{

    string  Result;
    ostringstream oss;
    oss << n;
    Result = oss.str();   
    return Result;
}
string DisplayFloat ( float f )
{
    string  Result;
    ostringstream oss;
    oss << f;
    Result = oss.str();
    return Result;
}
*/
//--------------------------------------------------------------
//              Sorting
//--------------------------------------------------------------

 
void Sort_stringlist(stringlist& my_stringlist)
{
	//vector<string>::iterator it
	my_stringlist.sort (   ); //wcscmp
	//return my_stringlist;
}

