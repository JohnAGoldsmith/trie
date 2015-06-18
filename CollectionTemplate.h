// Pair-of-tries class template
// Copyright © 2009 The University of Chicago
#ifndef COLLECTIONTEMPLATE_H
#define COLLECTIONTEMPLATE_H
#include <iostream>  
#include <algorithm>     /* sort */
#include "trie.h"
#include "stringsurrogate.h" 
//#include "generaldefinitions.h"

#include "CompareFunc.h"
#include <list>
#include <vector>
#include <memory> 
#include <list> 
 
 
 
class prefix;
class parse;
class stem;
class suffixcollection;
class prefixcollection;
class stemcollection;
class CMiniLexicon;


template<class T> 
class TCollection : public CTrie 
{
protected:
	CMiniLexicon*   m_pMiniLex;
	int 		m_Count;
	int 		m_CorpusCount;
	bool 		m_DeletePointers;
	int* 		m_DeletionArray;
	bool 		m_HashHasChangedFlag;
	string 		m_MemberName;
	std::list<T*>	m_PointerList;
	std::vector<T*>	m_PointerVector;
	CTrie* 		m_pReverseTrie;
	std::list<CNode> 	m_pTerminalNodeList;
	std::vector<T*>	m_SortVector;
	bool 		m_SortValidFlag;
//	enum eSortStyle m_SortStyle;
	double 		m_TotalUseCount;
		
public:
	// construction/destruction.
//-----------------------------------------------------------------------#
	TCollection(){

	int 		m_Count			= 0;
	int 		m_CorpusCount 		=0;
	bool 		m_DeletePointers 	= false;
	int* 		m_DeletionArray 	=  NULL;
	//bool 		m_HashHasChangedFlag 	= false;
	string 		m_MemberName 		= "";
 
	bool 		m_SortValidFlag 	= NULL;
//	enum eSortStyle m_SortStyle 		= NO_SORT;
	double 		m_TotalUseCount 	= 0;
 
	}
;
//-----------------------------------------------------------------------#
	TCollection(string MemberName );
	//TCollection(CMiniLexicon* Lex, string MemberName = string());
	TCollection(CMiniLexicon* Lex);
//-----------------------------------------------------------------------#
	~TCollection(){
//		if ( m_PointerArray )      { delete [] m_PointerArray; m_PointerArray = NULL;  }
//		if ( m_SortArray )         { delete [] m_SortArray; m_SortArray = NULL;  }
//		if ( m_DeletionArray)      { delete [] m_DeletionArray; m_DeletionArray = NULL; }
		//if ( m_pTerminalNodeArray ) { delete [] m_pTerminalNodeArray; m_pTerminalNodeArray = NULL; }
		//if ( m_pReverseTrie )       { delete m_pReverseTrie; m_pReverseTrie = NULL; }
	};

	// disable copy
private:	
	TCollection(const TCollection& x);
	TCollection& operator=(const TCollection& x);
public:
//-----------------------------------------------------------------------#
 


  T* operator<< (string& szWord)
{
  CNode*    pTerminal;
  int      Result;
  char*    pKey;
  if ( szWord.length() == 0 ) { return NULL; }

  pKey = new char [ szWord.length()];
  LxStrCpy( szWord, pKey, szWord.length() );

  pTerminal = TrieInsert (stringsurrogate( pKey, 0, szWord.length() ), &Result);

	if (Result == 1) {
		std::auto_ptr<T> morpheme(new T(szWord ));
		morpheme->SetIndex(GetCount() - 1);
		pTerminal->SetPointer(morpheme.release());
	}
	T* pT = static_cast<T*>(pTerminal->Get_T_Pointer());

  
  IncrementCorpusCount(1);
  pT->IncrementCorpusCount(1);

  m_SortValidFlag      = false;
  m_HashHasChangedFlag  = true;
  if (m_ReverseFlag) { delete  pKey; }

  return pT;

}	 
//-----------------------------------------------------------------------#
	T* operator<< ( stringsurrogate SS)
	{
	  std::cout << "\n line 83 of Collection Template, using SS for operator<<, m_PointerList" ;
	  char*		szWord = new char[SS.GetLength()];
	  CNode*	pTerminal;
	  int		Result;

	  LxStrCpy( &SS, szWord, SS.GetLength() );
	  
	  pTerminal = TrieInsert ( stringsurrogate(szWord,0,SS.GetLength()), &Result ); // in the underlying trie

	  if (Result == 1) {
			std::auto_ptr<T> morpheme(new T(SS));
			//morpheme->SetIndex(GetCount() - 1);           Maybe this should go back in???
			pTerminal->SetPointer(morpheme.release());
			m_Count++;
	  }
	  T* pT = static_cast<T*>(pTerminal->Get_T_Pointer());
	  m_PointerList.push_back(pT);

 

	  //IncrementCorpusCount(1);
	  pT->IncrementCorpusCount(1);
	  //cout << "\nline 110" << m_Count; 
	  m_SortValidFlag      = false;
	  m_HashHasChangedFlag  = true;

	  delete [] szWord;

	  return pT;           
	}

//------------------------------------------------------------------------#
//------------------------------------------------------------------------#
	T* operator^= ( parse* );
//------------------------------------------------------------------------#
	T* operator^= ( stringsurrogate string){
	if (string.GetLength() < 1)
		return 0;
	if (CNode* node = Find1(string))
		return static_cast<T*>(node->Get_T_Pointer());
	return 0;
};
//------------------------------------------------------------------------#
 T*  operator^=(string string)
{
	if (string.length() == 0)
		return 0;
	if (CNode* node = Find1(stringsurrogate(string)))
		return static_cast<T*>(node->Get_T_Pointer());
	return 0;
}
//------------------------------------------------------------------------#
T*   operator[] ( int n)
{
  if ( m_PointerList.size() == 0 || m_HashHasChangedFlag == true )
  {
    CreatePointerVector();
  }
 

  return m_PointerVector[n];
}
//------------------------------------------------------------------------#
void AddPointer( T* pT)
 
	{
	  CNode*    pTerminal;
	  stringsurrogate    ssWord = pT->GetKey();

	  pTerminal = CTrie::operator<< (ssWord);
	  pTerminal->SetPointer ( pT );

	  // Add to the reverse trie also
	  if( m_pReverseTrie )
	  {
	    ssWord.SetBackwards(true);
	    pTerminal = m_pReverseTrie->TrieInsert( ssWord );
	    pTerminal->SetPointer(pT);
	  }
	  
	  pT->SetIndex ( GetCount() - 1);
	  IncrementCorpusCount(pT->GetCorpusCount());
	}

 
//------------------------------------------------------------------------#
	T*				AddToCollection(stringsurrogate  this_ss)
{  
	  
	  m_HashHasChangedFlag = true;

 
	 // cout << "\n line 180 of CollectionTemplate.h using string for operator ";
	  char*		szWord = new char[this_ss.GetLength()];
	  CNode*	pTerminal;
	  int		Result;

	  LxStrCpy( &this_ss, szWord, this_ss.GetLength() );
	  
	  pTerminal = TrieInsert ( stringsurrogate(szWord,0,this_ss.GetLength()), &Result ); // in the underlying trie

	  if (Result == 1) {
			std::auto_ptr<T> morpheme(new T(this_ss));
			//morpheme->SetIndex(GetCount() - 1);           Maybe this should go back in???
			pTerminal->SetPointer(morpheme.release());
			m_Count++;
	  }
	  T* pT = static_cast<T*>(pTerminal->Get_T_Pointer());
	  m_PointerList.push_back(pT);


 
	  IncrementCorpusCount(1);
	  pT->IncrementCorpusCount(1);
 
	  m_SortValidFlag      = false;
	  m_HashHasChangedFlag  = true;

	  delete [] szWord;

 	  m_Count++; 
	  return pT;
}
//------------------------------------------------------------------------#
	T*				AddToCollection(string&   Word)
{
 
	  		m_HashHasChangedFlag = true;
	  char*		szWord = new char[Word.length()];
	  CNode*	pTerminal;
	  int		Result;

	  LxStrCpy( Word, szWord, Word.length() );
	  
	  pTerminal = TrieInsert ( stringsurrogate(szWord,0,Word.length()), &Result ); // in the underlying trie
 
	
	  if (Result == 1) {
			std::auto_ptr<T> morpheme(new T(Word));
			 
			pTerminal->SetPointer(morpheme.release());
			m_Count++;
	  }
	  T* pT = static_cast<T*>(pTerminal->Get_T_Pointer());
	   
	  m_PointerList.push_back(pT);
	 

	 
	  pT->IncrementCorpusCount(1);
 
	  m_SortValidFlag      = false;
	  m_HashHasChangedFlag  = true;

	  delete [] szWord;

	
	  m_Count++; 
	  return pT;
}
//------------------------------------------------------------------------#

 
bool  Contains ( stringsurrogate& string )
{
  T* pT = *this ^= string;
  if ( pT )
  {
    return true;
  }
  else
  {
    return false;
  }
}
//------------------------------------------------------------------------#
	void		CreatePointerVector()
	{
		std::cout << "  we are in create pointer vector";
		typename std::list<T*>::iterator pointerlistiter ;
		const int size = m_PointerList.size();
		std::cout << " ...size is " << size;
		m_PointerVector.reserve(size);
		int i = 0;
		for  ( pointerlistiter  = m_PointerList.begin();
		       pointerlistiter != m_PointerList.end();
		       pointerlistiter++)
			{ m_PointerVector.push_back(*pointerlistiter);}
			
	 

		m_HashHasChangedFlag = false;
	};
//------------------------------------------------------------------------#

 
void  CreateReverseTrie()
{
  CNode*            pTerminal;
  stringsurrogate  ssKey;
  
  if( m_pReverseTrie ) delete m_pReverseTrie;
  m_pReverseTrie = new CTrie( true );
  m_pReverseTrie->SetAutoDelete( false );

	// Build the reverse trie from the
	// forward trie
	for (int i = 0; i < GetCount(); ++i)
		if (T* pT = GetAt(i)) {
			ssKey = pT->GetKey();
			ssKey.SetBackwards();
			pTerminal = m_pReverseTrie->TrieInsert(ssKey);
			pTerminal->SetPointer(pT);
		}
}
 
void  DoNotDeletePointers()
{
  m_DeletePointers = false;
}
//-----------------------------------------------------------------------#
	void				DumpVisibleToLogFile();
//-----------------------------------------------------------------------#
	void Empty(){
			  ResetToEmpty();
 
			m_PointerList.clear();
			m_PointerVector.clear();
			m_SortVector.clear();
			  m_CorpusCount        = 0;
			  m_SortValidFlag      = false;
			  m_HashHasChangedFlag = true;
			};
//-----------------------------------------------------------------------#
 
	T*				GetAt( int n)
{
	//cout << "\nWe are in GetAt in collection template\n";
	  if ( m_PointerVector.size() == 0 || m_HashHasChangedFlag == true )
	  {
	    CreatePointerVector();
	    std::cout << "\nWe created the pointer vector"; 
	  }
	
  return m_PointerVector[n];
};
//-----------------------------------------------------------------------#
 
stringsurrogate GetAt_SS( int n )
{
  stringsurrogate Return ( GetAt(n)->GetKeyPointer(), 0, GetAt(n)->GetKeyLength() );

  return Return;
}
 
//-----------------------------------------------------------------------#

	int 				GetCorpusCount() const;
//-----------------------------------------------------------------------#

CTrie*  GetReverseTrie()
{
	if( !m_pReverseTrie ) CreateReverseTrie();
	return m_pReverseTrie;
}
//-----------------------------------------------------------------------#
int  GetSortValidFlag()
{
  return m_SortValidFlag;
}
//-----------------------------------------------------------------------#
    	int 				GetTotalUseCount() { return m_TotalUseCount; }
//-----------------------------------------------------------------------#
	 
CTrie*   GetTrie()
{
	return this;
}
//-----------------------------------------------------------------------#
 
int  GetWidth( stringsurrogate string )// i.e., from Trie
{
  CNode *pNode = Find1 ( string );
  return pNode->GetWidth();
}

//-----------------------------------------------------------------------#
	void				IncrementCorpusCount( int n = 1 ) {m_CorpusCount += 1;}
//-----------------------------------------------------------------------#
 
void RecomputeCorpusCount()
{
  m_CorpusCount = 0;
  for (int i = 0; i < GetCount(); i++)
  {
    m_CorpusCount += GetAt(i)->GetCorpusCount();
  }
  return;
}
 
//------------------------------------------------------------------------#
void	RemoveAll()
	{
 

	  ResetToEmpty();
 
	};

//------------------------------------------------------------------------#
 
//------------------------------------------------------------------------#
 
//------------------------------------------------------------------------#
/*
bool				RemoveMember( const stringsurrogate & ssT, bool DeleteFlag) // FSA
{

  bool    bResult;

  bResult = RemoveFromTrie ( ssT, DeleteFlag );

  if ( bResult )
  {
    m_SortValidFlag      = false;
    m_HashHasChangedFlag  = true;
    if( m_pReverseTrie )
    {
      stringsurrogate ss_copy = ssT;
      ss_copy.SetBackwards();
      if (!m_pReverseTrie->RemoveFromTrie(ss_copy))
        assert( !"bool TCollection<T>::RemoveMember ( stringsurrogate& ssT ) : Type existed in forward trie but not reverse trie." );
      ss_copy.SetBackwards(false);
    }

    return true;
    return true;
  }
  else
  {
    return false;
  }
}
*/
//------------------------------------------------------------------------#
 
//------------------------------------------------------------------------#

	void				SetKey( T*, parse& );
//------------------------------------------------------------------------#

	void				SetKey( T*, string );
//------------------------------------------------------------------------#

 
//------------------------------------------------------------------------#

 
void   SetSortValidFlag(bool value)
{
	m_SortValidFlag = value;
}
 
//------------------------------------------------------------------------#
	  
//void  Sort( eSortStyle SS )
void 	Sort()
	{
	  int i;

 
	  int Size = GetCount();
	  m_SortVector.clear();
	  m_SortVector.reserve(Size);
 	  for (i = 0; i < Size; i++)
	  {
	    m_SortVector[i] = GetAt( i );
	  }
 
	  sort(m_SortVector.begin(), m_SortVector.end(), CompareAlphabetically);
 

	  for ( i = 0; i < Size; i++)
	  {
	    m_SortVector[i]->SetSortIndex(i);
	  }

 
	  m_SortValidFlag = true;

}


 
 
 
}
#include "CollectionTemplate.tcc"


#endif // COLLECTIONTEMPLATE_H
