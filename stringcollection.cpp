 
 
#include <iostream>  
#include <algorithm>     /* sort */
#include "trie.h"
#include "stringsurrogate.h" 
//#include "generaldefinitions.h"


#include <list>
#include <vector>
#include <memory> 
#include <string>
#include "CompareFunc.h"
#include "stringcollection.h" 
 
class parse;
class stringobject;
 
stringcollection::stringcollection()
{
	std::cout << "making a string collection"<<std::endl;		 
 	trie*		m_trie			= new trie();
    int 		m_Count			= 0;
	int 		m_CorpusCount 		= 0;
	bool 		m_DeletePointers 	= false;
	//int* 		m_DeletionArray 	= NULL;	 
	string 		m_MemberName 		= "";
 	bool 		m_SortValidFlag 	= NULL;
	//enum eSortStyle m_SortStyle 		= NO_SORT;
	double 		m_TotalUseCount 	= 0;
std::cout << "In StringCol::word count "<<m_Count<<std::endl;
std::cout << "In StringCol::trie "<<m_trie<<std::endl;
};
 
stringcollection::stringcollection(const stringcollection& sc)
{
	std::cout << "copying a string collection"<<std::endl;		 
 	trie*		m_trie			= new trie(sc.GetTrie());
    int 		m_Count			= sc.GetCount();
	int 		m_CorpusCount 		= sc.GetCorpusCount();
	bool 		m_DeletePointers 	= false;
	//int* 		m_DeletionArray 	= NULL;	 
	string 		m_MemberName 		= "";
 	bool 		m_SortValidFlag 	= NULL;
	//enum eSortStyle m_SortStyle 		= NO_SORT;
	double 		m_TotalUseCount 	= sc.GetTotalUseCount();
std::cout << "In StringCol::word count "<<m_Count<<std::endl;
std::cout << "In StringCol::trie "<<m_trie<<std::endl;
};
 
stringcollection::stringcollection(string MemberName ){
 
 	trie*		m_trie			= new trie();
	int 		m_Count			= 0;
	int 		m_CorpusCount 		= 0;
	bool 		m_DeletePointers 	= false;
	//int* 		m_DeletionArray 	=  NULL;	 
	string 		m_MemberName 		= MemberName;
 	bool 		m_SortValidFlag 	= NULL;
	//	enum eSortStyle m_SortStyle 		= NO_SORT;
	double 		m_TotalUseCount 	= 0;
 
 
	};;
	 
	 

stringcollection::~stringcollection(){
		std::cout << "destroying a string collection"<<std::endl;
		 if (m_trie) 			{ delete m_trie;}

	};

  
//-----------------------------------------------------------------------#

stringobject* stringcollection::operator<< (string& szWord)
{
  CNode*	pTerminal;
  int      	Result;
  char*    	pKey;
  if ( szWord.length() == 0 ) { return NULL; }

  pKey = new char [ szWord.length()];
  LxStrCpy( szWord, pKey, szWord.length() );

  pTerminal = m_trie->TrieInsert (stringsurrogate( pKey, 0, szWord.length() ), &Result);

	if (Result == 1) {
		std::auto_ptr<stringobject> pwordobject (new stringobject(szWord ));
		pwordobject->SetIndex(m_trie->GetCount() - 1);
		pTerminal->SetPointer(pwordobject.release());
	}
	stringobject* pT = static_cast<stringobject*>(pTerminal->Get_T_Pointer());

  
  IncrementCorpusCount(1);
  pT->IncrementCorpusCount(1);

  m_SortValidFlag      = false;
  m_HashHasChangedFlag  = true;
  if (m_ReverseFlag) { delete  pKey; }

  return pT;

}	 
  
//------------------------------------------------------------------------#
//	string* stringcollection::operator^= ( parse* );
//------------------------------------------------------------------------#
	stringobject* stringcollection::operator^= ( stringsurrogate string){
	if (string.GetLength() < 1)
		return 0;
	if (CNode* node = m_trie->Find1(string))
		return static_cast<stringobject*>(node->Get_T_Pointer());
	return 0;
};
//------------------------------------------------------------------------#
 stringobject*  stringcollection::operator^=(string string)
{
	if (string.length() == 0)
		return 0;
	if (CNode* node = m_trie->Find1(stringsurrogate(string)))
		return static_cast<stringobject*>(node->Get_T_Pointer());
	return 0;
}
//------------------------------------------------------------------------#
stringobject*   stringcollection::operator[] ( int n)
{
  if ( m_PointerList.size() == 0 || m_HashHasChangedFlag == true )
  {
    CreatePointerVector();
  }
 

  return m_PointerVector[n];
}
//------------------------------------------------------------------------#
void stringcollection::AddPointer( stringobject* pT)
 
	{
	  CNode*		pTerminal;
	  string		word = pT->GetKey();
	  stringsurrogate       ssWord = stringsurrogate(word);
	  			pTerminal = m_trie->TrieInsert(ssWord) ;
	  			pTerminal->SetPointer ( pT );

	  // Add to the reverse trie also
	  if( m_pReverseTrie )
	  {
	    ssWord.SetBackwards(true);
	    pTerminal = m_pReverseTrie->TrieInsert( ssWord );
	    pTerminal->SetPointer(pT);
	  }
	  
	  pT->SetIndex ( m_trie->GetCount() - 1);
	  IncrementCorpusCount(pT->GetCount());
	}

 
//------------------------------------------------------------------------#
	stringobject*	stringcollection::AddToCollection(string    Word)
{
	  		m_HashHasChangedFlag = true;
	  char*		szWord = new char[Word.length()];
	  CNode*	pTerminal;
	  int		Result;

	  LxStrCpy( Word, szWord, Word.length() );
	  
	  pTerminal = m_trie->TrieInsert ( stringsurrogate(szWord,0,Word.length()), &Result ); // in the underlying trie
 
	
	  if (Result == 1) {
			std::auto_ptr<stringobject> morpheme(new stringobject(Word));
			 
			pTerminal->SetPointer(morpheme.release());
			m_Count++;
	  }
	  stringobject* pT = static_cast<stringobject*>(pTerminal->Get_T_Pointer());
	   
	  m_PointerList.push_back(pT);
	 

	 
	  pT->IncrementCorpusCount(1);
 
	  m_SortValidFlag      = false;
	  m_HashHasChangedFlag  = true;

	  delete [] szWord;

	
	  m_Count++; 
	  return pT;
}
//------------------------------------------------------------------------#

 
bool  stringcollection::Contains ( stringsurrogate  string )
{
  stringobject* pT = *this ^= string;
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
void		stringcollection::CreatePointerVector()
{
		 
		typename std::list<stringobject*>::iterator pointerlistiter ;
		const int size = m_PointerList.size();
		 
		m_PointerVector.reserve(size);
		int i = 0;
		for  ( pointerlistiter  = m_PointerList.begin();
		       pointerlistiter != m_PointerList.end();
		       pointerlistiter++)
			{ m_PointerVector.push_back(*pointerlistiter);}
			
	 

		m_HashHasChangedFlag = false;
};
//------------------------------------------------------------------------#
 
void  stringcollection::DoNotDeletePointers()
{
  m_DeletePointers = false;
}
//-----------------------------------------------------------------------#
	void				DumpVisibleToLogFile();
//-----------------------------------------------------------------------#
void stringcollection::Empty(){
	m_trie->ResetToEmpty();
 	m_PointerList.clear();
	m_PointerVector.clear();
	m_SortVector.clear();
	m_CorpusCount        = 0;
	m_SortValidFlag      = false;
	m_HashHasChangedFlag = true;
	};
//-----------------------------------------------------------------------#
 
stringobject*	stringcollection::GetAt( int n)
{
	if ( m_PointerVector.size() == 0 || m_HashHasChangedFlag == true )
	{
	    CreatePointerVector();
	    std::cout << "\nWe created the pointer vector"; 
	}
	return m_PointerVector[n];
};
//-----------------------------------------------------------------------#
 
//-----------------------------------------------------------------------#

	int 	stringcollection::GetCorpusCount() const  {return m_CorpusCount;}
//-----------------------------------------------------------------------#
 
//-----------------------------------------------------------------------#
int  stringcollection::GetSortValidFlag()
{
  return m_SortValidFlag;
}
//-----------------------------------------------------------------------#
    	int 				stringcollection::GetTotalUseCount() const
 { return m_TotalUseCount; }
//-----------------------------------------------------------------------#
	 
const trie*   stringcollection::GetTrie() const
{
	return m_trie;
}
//-----------------------------------------------------------------------#
 
int  stringcollection::GetWidth( stringsurrogate string )// i.e., from Trie
{
  CNode *pNode = m_trie->Find1 ( string );
  return pNode->GetWidth();
}

//-----------------------------------------------------------------------#
	void stringcollection::IncrementCorpusCount( int n   ) {m_CorpusCount += 1;}
//-----------------------------------------------------------------------#
 
void stringcollection::RecomputeCorpusCount()
{
  m_CorpusCount = 0;
  for (int i = 0; i < m_trie->GetCount(); i++)
  {
	m_CorpusCount += GetAt(i)->GetCount();
  }
  return;
}
 
//------------------------------------------------------------------------#

	void	stringcollection::stringcollection::SetKey( string*, parse& ){};
//------------------------------------------------------------------------#

	void	stringcollection::SetKey( string*, string ){};
//------------------------------------------------------------------------#

 
//------------------------------------------------------------------------#

 
void   stringcollection::SetSortValidFlag(bool value)
{
	m_SortValidFlag = value;
}
 
//------------------------------------------------------------------------#
	  
//void  Sort( eSortStyle SS )
void 	stringcollection::Sort()
{
	  int i; 
	  int Size = m_trie->GetCount();
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


 
 
 
  
