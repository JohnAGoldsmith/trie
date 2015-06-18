// Pair-of-tries class template
// Copyright © 2009 The University of Chicago
#ifndef COLLECTIONTEMPLATE_H
#define COLLECTIONTEMPLATE_H
#include <iostream>  
#include <algorithm>     /* sort */
#include "trie.h"
//#include "stringsurrogate.h" 
//#include "generaldefinitions.h"

//#include "CompareFunc.h"
#include <list>
#include <vector>
#include <memory> 
 
 
 
 
 
class parse;
 

class stringobject 
{
protected:
	string 	m_string;	
	int 	m_count;
	int 	m_index;
	int 	m_sortindex;
public:
	stringobject(string key, int count = 0){m_string=key;m_count=count;}
	void 	SetIndex (int  n) {m_index = n;}
	void 	SetSortIndex(int n) {m_sortindex =n;}
	int 	GetCount () {return m_count;}
	void 	IncrementCorpusCount (int n) {m_count += n;}
	string  GetKey() {return m_string;}
};

 
class stringcollection 
{
protected:
	trie*				m_trie;
	 
	int 				m_Count;
	int 				m_CorpusCount;
	bool 				m_DeletePointers;
	int* 				m_DeletionArray;
	bool 				m_HashHasChangedFlag;
	string 				m_MemberName;
	std::list<stringobject*>	m_PointerList;
	std::vector<stringobject*>	m_PointerVector;
	trie* 				m_pReverseTrie;
	std::list<CNode> 		m_pTerminalNodeList;
	std::vector<stringobject*>	m_SortVector;
	bool 				m_SortValidFlag;
//	enum eSortStyle 		m_SortStyle;
	double 				m_TotalUseCount;
	bool				m_ReverseFlag;
		
public:
	// construction/destruction.

	stringcollection();
 
	stringcollection(string MemberName );
	 
	 
	~stringcollection();

	// disable copy
private:	
	stringcollection(const stringcollection& x);
	stringcollection& operator=(const stringcollection& x);
public:
 
  	stringobject* 	operator<< (string& szWord);
	string* 	operator<< ( stringsurrogate SS);
 	string* 	operator^= ( parse* );
 	stringobject* 	operator^= ( stringsurrogate string) ;
	stringobject*  	operator^=(string string);
 	stringobject*   operator[] ( int n);
 
 	void 		AddPointer( stringobject* pT);
 	stringobject*	AddToCollection(string    Word);
 	bool  		Contains ( stringsurrogate  string );
 	void		CreatePointerVector();
	void  		DoNotDeletePointers();
 	void		DumpVisibleToLogFile();
	void 		Empty(); 
	stringobject*	GetAt( int n);
	int		GetCount() const {return m_Count;}
 	int  		GetSortValidFlag();
    	int 		GetTotalUseCount() const ;
 	const trie*   	GetTrie() const;
	int  		GetWidth( stringsurrogate string );// i.e., from Trie;
	void		IncrementCorpusCount( int n = 1 );
 	int		GetCorpusCount() const;
 	void 		RecomputeCorpusCount();
	//void		RemoveAll()
	void		SetKey( string*, parse& );
 	void		SetKey( string*, string );
	//void   	SetSortStyle(eSortStyle SS);
	void   		SetSortValidFlag(bool value);
	//void  	Sort( eSortStyle SS )
	void 		Sort();
	//string*	AddToCollection(stringsurrogate  this_ss)

}; 
#endif // COLLECTIONTEMPLATE_H
