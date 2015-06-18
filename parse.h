// Partitioned-string type
// Copyright © 2009 The University of Chicago
#ifndef PARSE_H
#define PARSE_H
 
//#include <assert.h>
#include <map>
class parse;
#include <string>
#include <vector>
//using std::string;
//using namespace std;
 
#include "stringsurrogate.h"
#include "StringFunc.h" 


//template<class K, class V> class QMap;



/// A parse is a string (i.e., vector of char) partitioned into continguous
/// segments.  In Linguistica, such objects are used in a few different ways:
///  * as a general purpose string value type (i.e., as the underlying storage
///    for stringsurrogates)
///  * as a general purpose list-of-strings type
///  * to represent a word parsed into morphemes.
///
/// Segment indices are 1-based to allow considering the beginning of
/// the string as the “end of segment 0”.
//  m_Pieces's length must always be at least 1 greater than PieceCount;
//  though m_Pieces[0] is always 0.
//	xx xxx xx:	is represented:
//	0 2 5 7
//  so Piece[1] goes from Key[m_Pieces[0]] to
//						  Key[m_Pieces[1] - 1];
//  Piece[2] goes from  Key[m_Pieces[1]] to
//						Key[m_Pieces[2]-1]
//	abcd
//  m_Pieces array:
//  0  4; so Piece[1] goes from Key[m_Pieces[0]] to
//							to Key[m_Pieces[1] - 1];
//	Key's length will alway be m_Pieces[ PieceCount ];
//  And: this + m_Pieces[ k ] points to the beginning of Piece # k
class parse {
public:
	enum sort_style {
		eNotSorted,
		eAlphabetized,
		eAlphabetizedFromEnd,
		eSortByPieceLength
	};
protected:
	/// beginning of managed string
	char* m_Key;
	/// length allocated for string use
	int m_AllocatedLength;
	/// length of string --- i.e., length of the user-visible portion
	/// (so m_KeyLength <= m_AllocatedLength)
	int m_KeyLength;

	/// offsets for ends of segments.
	/// (so m_Pieces[0] == 0)
	int* m_Pieces;
	/// values associated to segments (for general use)
	/// m_PieceValues[0] is unused
	double* m_PieceValues;
	/// number of segments.
	/// (the last segment has index m_PieceCount)
	int m_PieceCount;
	/// length allocated for m_Pieces, m_PieceValues use
	/// (m_LengthOfPieceVector >= m_PieceCount + 1)
	int m_LengthOfPieceVector;

	/// default value for new pieces
	double m_DefaultPieceValue;

	/// alphabetize inserted strings?
	enum sort_style m_SortStyle;

	/// extra tidbit for general use!
	float m_Evaluation;


	int m_CorpusCount;

	// should these be here? Maybe shift to another height in the hierarachy
	int m_Index;
	int m_SortIndex;   

	parse*  m_AlphabetizedForm;   
public:
	// construction/destruction.
	parse(const string & this_string,double DefaultPieceValue=0.0);
	parse(double default_piece_value = 0.0);
	parse(const parse&, double = 0.0);
        //parse(const string&);
        parse(const stringsurrogate&);
        parse(const stringsurrogate&, double);
	parse(const char&, double = 0.0);
	virtual ~parse();

	// copy.

	parse& operator=(const parse& Parse) 	{ CopyParse(Parse); 	return *this; }
	parse& operator=(const parse* pParse)	{ CopyParse(*pParse); 	return *this; }
	parse& operator=(const char& ch) 	{ SetKey(ch); 		return *this;}
        parse& operator=(const stringsurrogate SS);
	void CopyParseStructure(const parse&);
	void CopyParseStructureWithoutBoundaries(const parse&);
	void Absorb_stringlist(stringlist&);
	void CopyParse(const parse&);
        void Collapse(const stringsurrogate&, const char& = ' ');
	void IngestSignature(const string);
        void SetKey(const stringsurrogate);
	void SetKey(const char*, int);
	void SetKey(const char&);
	void SetKey(const parse&);
	void SetKey(const parse* Parse) { SetKey(*Parse); };
	void SetKey(const string&  mystring);

	// move.

	void swap(parse& other);
	/// XXX. deletes key twice!
	void TakeLeft(const parse&, int);
	void TakeLeft(const parse* pParse, int n) { TakeLeft(*pParse, n); }
	void TakeRight(const parse&, int);
	void TakeRight(const parse* pParse, int n) { TakeRight(*pParse, n); }

	// clear.

	void ClearParse();

	/// assign alphabetized list of the trigrams in str
	void FindAlphabetizedTrigrams(char* str, int len);
	/// assign underlying string
	void ClearParseStructure();
	/// assign underlying string, but remember 0th piece value.
	void SimplifyParseStructure();

	// append/insert.

	void operator<<(double n) { Append(n); }
	void operator<<(int n) { Append(n); }
	void operator<<(const parse* Parse) { Append(Parse); }
        void operator<<(const stringsurrogate SS);
	parse operator+=(const parse*);
        parse operator+=(const stringsurrogate);
        void Append(const stringsurrogate str);
	void Append(const char& ch);
	void Append(double piece);	///< Append(QString::number(piece))
	void Append(int piece);	///< Append(StringToIntWithCommas(piece))
	void Append(const parse& str);
        void Append(const string& str) { Append(stringsurrogate(str)); }

	/// deprecated
	void Append(const parse* str) { Append(*str); }
	void AppendCR();
	void AppendHyphen();
        void AppendLine(const stringsurrogate& line);
	void AppendNewLine();
	void AppendNoCommas(int piece);
	void AppendTab();
        void AppendInAlphabeticalOrder(const stringsurrogate&,
		bool IsTemplateOperator = false);
	void AppendInAlphabeticalOrder(const parse*);

	// concatenate.

	parse operator+(const parse*) const;
        parse operator+(const stringsurrogate) const;

	// remove.

        parse operator-=(const stringsurrogate);
	/// Remove the first segment that compares equal to piece.
	/// If no such segment exists, do nothing.
        void Remove(const stringsurrogate& piece);
	/// Requires: 1 <= i <= m_PieceCount
	/// erase i'th piece
	void RemovePiece(int i);

	// split segment.

	void operator/=(int i);
	void CutNFromTheLeft(int);
	void CutNFromTheRight(int);
	void CutRightBeforeHere(int);

	// merge/combine segments.

	void MergePieces(int);

	// move inter-segment cut.

	void MoveThisManyLettersLeftwardFromArg1(int, int);
	void MoveThisManyLettersRightwardFromArg1(int, int);
	void SetBreak(int, int);

	// number of segments.

	int Size() const { return m_PieceCount; }

	// segment access.

	stringsurrogate	    GetKeySS();
	int 		    GetKeyLength() {return m_KeyLength;}
        stringsurrogate     operator[](int) const;
        stringsurrogate     GetLastPiece() const;
        const stringsurrogate     GetPiece(int) const;
        string              GetPieceAsString (int) const;
        int*                GetPieces()    const { return m_Pieces; }
        int                 GetPositionOfFirstCharOfThisPiece(const int) const;
        stringsurrogate     ThisPieceAndWhatFollows(int) const;
        int                 ThisPieceLength(int) const;
        stringsurrogate     UpToAndIncludingThisPiece(int) const;
        stringsurrogate     WhatPrecedesPiece(int) const;
        int                 GetPieceLoc(int piececount)
	{		 
		return m_Pieces[piececount];
	}
	int			GetCorpusCount ()const {return m_CorpusCount;}
	void 			IncrementCorpusCount(int n){m_CorpusCount += n;}
	void 			SetCorpusCount (int n) {m_CorpusCount = n;}
	// general-purpose segment data

	double GetPieceValue(int) const;
	double* GetPieceValues() const { return m_PieceValues; }
	/// Find a particular "piece" of the parse, and
	/// increment its value-count.
        void IncrementPieceValue(stringsurrogate, double);
	void SetPieceValue(int, double);

	// entire string

        stringsurrogate GetKey() const;
	stringsurrogate GetSS() const; //same as above.
	int GetKeyLength() const { return m_KeyLength; }

	// substring.

        stringsurrogate operator()(int, int) const; // in underlying string
        stringsurrogate Mid(int, int) const;
        stringsurrogate Left(int) const;
        stringsurrogate Right(int) const;

	// character access.
	char GetChar(int) const;

	// comparison.

	bool operator==(const parse*) const;
	bool operator!=(const parse* Parse) const
	{ return !(*this == Parse); }

	// maintaining sort.

		
	void 	SetSortIndex(int n) {m_SortIndex = n;}
	enum sort_style GetSortStyle() const { return m_SortStyle; }
	void SetSortStyle(enum sort_style e) { m_SortStyle = e; }
	void NotAlphabetized() { m_SortStyle = eNotSorted; }

	// sort.
	

	void Alphabetize();
	/// Sort pieces in lexicographical order, reading each right-to-left.
	void ReverseAlphabetize();
	/// Sort the pieces of the parse by piece lengths,
	/// in decreasing size.
	void SortByPieceLength();
	/// Sort the pieces of the parse by the PieceValues.
	void SortByValue();

	// queries.

	bool AreAllPiecesSingletons() const;
	int CountOverlapAlphabetized(parse&);
	/// Index for the first segment that compares equal to piece.
	/// If no such segment exists, result is 0.
        int Find(const stringsurrogate& piece) const;
	bool IsAlphabetical() const;
	bool IsProperName() const;

	// split/parse.

	void Tokenize();

	// conversion to string, stringlist

        stringlist& Create_stringlist(stringlist&) const;
	string Display();
        string Display(const char, string2string* filter = NULL) const;
        string Display(string2string* filter = NULL) const;

	// prefix/suffix extraction helpers.

	int DeleteLastCharsOfAllPieces(int, parse&) const;
	int DeleteLeadingCharsOfAllPieces(int, parse&) const;
	char FindCommonFirstLetterFromAll() const;
	char FindCommonLastLetterFromAll() const;
	parse RipOut(char, parse* = 0) const;
	bool TestIfCharPlusSigEqualsThis(const parse&, const char) const;
        void PrefixToAllPieces(const stringsurrogate&);
        void PrefixToAllPieces2(const stringsurrogate&);
	void PrefixToAllPieces(const char ch);
        void RemovePiecesThatDoNotBegin(const stringsurrogate&);
        void RemovePiecesThatDoNotEnd(const stringsurrogate&);
        void RemovePiecesThatBegin(const stringsurrogate&);
        void RemovePiecesThatEnd(const stringsurrogate&);
        void RemovePrefixFromAllPieces(const stringsurrogate&);
        void RemoveSuffixFromAllPieces(const stringsurrogate&);
        void SuffixToAllPieces(const stringsurrogate&);
        void SuffixToAllPieces2(const stringsurrogate&);
	void SuffixToAllPieces(const char ch);

	// extra general-purpose value.

	float GetEvaluation() const { return m_Evaluation; }
	void SetEvaluation(float e) { m_Evaluation = e; }

	// data, capacity.

	int GetAllocatedLength() const { return m_AllocatedLength; }
	char* GetKeyPointer() const { return m_Key; }
	int GetLengthOfPieceVector() const { return m_LengthOfPieceVector; }

	// set operations.

	parse Intersection(const parse&) const;
	bool Overlap(const parse&) const;
	void MergeParse(const parse&);
	void MergeParse(parse& OtherInput, parse& Output); // allomorphy. Change?
	void yuhuMergeParse(parse*);
	void MergeAndAlphabetizeParse(const parse&);
	bool Contains(const parse&) const;
	bool Contains(const string) const;
	bool Contains(const parse* pParse) const
	{ return Contains(*pParse); }
        bool Contains(const stringsurrogate&) const;
	bool ContainsNULL() const;

	// reverse.

	parse GetReverse() const;
	void ReverseMe();

	// rewrite a segment.

        void Replace(int, stringsurrogate&);

	// partially overwrite.

	void Fill(const char&, int);

	/// add a "\r\n" segment before each segment
	void InsertCRs();

	// description length.

	double ComputeComplexity() const;
	//virtual double ComputeDL(int char_count = 26) const;
	double ComputeDL(int char_count = 26) const;


	void SetAlphabetizedForm( );

protected:
	virtual void SetLengthOfPieceVector(int i)
	{ m_LengthOfPieceVector = i; }
private:
	void AddKeyLength(int);
	void AddSlots(int);

	void CheckSize(int, int);
	void SetPieceCount(int);

	 

 
};
//typedef parse::sort_style eParseSortStyle;

bool AnyOverlap(const parse&, const parse&);

//namespace std {
//	inline void swap(parse& x, parse& y) { x.swap(y); }
//}

#endif // PARSE_H
