// Implementation of trie methods
// Copyright © 2009 The University of Chicago

#include <memory>
#include <algorithm>
#include <stdlib.h>
#include "trie.h"
#include "assert.h" 
#include "stringsurrogate.h" 
#include <iostream>


typedef stringsurrogate CSS;
/*
#include <memory>
#include <vector>
#include <functional> 
#include "StringSurrogate.h"
#include "Parse.h"
#include "Stem.h"
#include "MorphemeCollection.h"
#include "WordCollection.h"
#include "CompareFunc.h"
 
 
*/
// trie
/////////////////////////////////////////////////////////////
 
trie::trie(bool ReverseFlag)
	:m_Root(new CNode()),
	m_NodeArray(NULL),
	m_ReverseFlag(ReverseFlag),
	m_AutoDelete(true),
	m_Count(0),
	m_NumberOfNodes(1),
	m_TrieHasChangedFlag(true),
	//m_TotalUseCount(0),
	m_IsAlphabetized(false) { 
	std::cout << "making a trie " << this << " "<<m_Count <<std::endl;
	}
 

 
trie::~trie()
{
	std::cout<<"destroying a trie"<<std::endl;
	if (m_Root)      {delete m_Root;}
	if (m_NodeArray) {delete[] m_NodeArray;}
}

void trie::ResetToEmpty()
{
	delete m_Root;	// destructor deletes all child nodes
	m_Root = new CNode();
	m_Count = 0;
	m_NumberOfNodes = 1;
	m_TrieHasChangedFlag = true;
	m_IsAlphabetized = false;
	// m_NodeArray, m_ReverseFlag, and m_AutoDelete remain unchanged.
}

CNode* trie::operator<< ( stringsurrogate ssS )
{
	return TrieInsert(ssS);
}

 
 
//----------------------------------------------------------------
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
//
//      Insert

CNode* trie::TrieInsert( stringsurrogate ssS, int* pResult )
{
  CNode* pNode = NULL;
   m_Root->NodeInsert(ssS, m_NumberOfNodes, &pNode, pResult);
   if ( pResult && *pResult == 1 )
  {
    m_Count++;
  }

  m_TrieHasChangedFlag  = true;
  m_IsAlphabetized    = false;

  return pNode;
}

CNode* trie::TrieInsert(stringsurrogate ssS)
{
  int Result        = 0;
  int* pResult      = &Result;
  CNode* pNode      = NULL;

  m_Root->NodeInsert(ssS, m_NumberOfNodes, &pNode, pResult);
  if ( pResult && *pResult == 1 )
  {
    m_Count++;
  }

  m_TrieHasChangedFlag  = true;
  m_IsAlphabetized    = false;

  return pNode;
}


//----------------------------------------------------------------
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
//
//

void trie::MakeATerminalPointerArray( CNode** Array )
{
  int Index = 0;

  m_Root->MakeATerminalPointerArray( Array, Index );
  assert ( (int) Index == m_Count );

}



int trie::CountValidSubstrings( stringsurrogate ss )
{
	return m_Root->CountValidSubstrings( ss );
}



CNode*    trie::Find1 ( stringsurrogate SS, bool PartialOK )
{
  CNode* pNode = m_Root->Find1(SS, PartialOK);
  return pNode;
}
//----------------------------------------------------------------
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
//
//      Remove
/*
bool   trie::RemoveFromTrie ( const stringsurrogate string, bool RemovePointerFlag )
{
  CNode*  pNode         = m_Root;
  CNode*  qNode         = NULL;
  m_TrieHasChangedFlag  = true;
  while ( pNode )   {
    for (int i = pNode->m_StartPoint + 1; i < pNode->m_BreakPoint; i++ )     {
      if ( string[i] != pNode->m_Key [i] )       {
        return false;
      }
    }
    char c             = string [ pNode->m_BreakPoint ];
    qNode               = pNode->FindLetter( c );
    if ( qNode == NULL )     {
      return false;
    }
    if (qNode->GetKey() == string )        {
        assert ( qNode->m_Pointer );
        qNode->m_ExistenceFlag = false;
	  
        if ( RemovePointerFlag && m_AutoDelete )   {
            delete qNode->m_Pointer;
        }
        qNode->m_Pointer = NULL;

        if ( qNode->m_Letters == NULL )       {
            delete qNode;
            m_NumberOfNodes--;

            char*  NewLetters      = new char [ pNode->GetNumberOfBranches() - 1 ];
            CNode**  NewPointers    = new CNode* [ pNode->GetNumberOfBranches() - 1 ];
            int k = 0;
                for (int j = 0; j < (int)pNode->GetNumberOfBranches(); j++)        {
                    if ( c == pNode->m_Letters[j] ) { continue; }
                    NewLetters[k] = pNode->m_Letters[j];
                    NewPointers[k] = pNode->m_Pointers[j];
                    k++;
            }
            assert ( k == (int)pNode->GetNumberOfBranches()-1 );
            delete [] pNode->m_Letters;  pNode->m_Letters  = NewLetters;
            delete [] pNode->m_Pointers; pNode->m_Pointers = NewPointers;
            pNode->SetNumberOfBranches(k);
      }
      else      {
        qNode->DoesNotExist();
      }
      m_Count--;
      return true;
    }
    else    {
      pNode = qNode;
      continue;
   }
  }
  assert (false);
  return false;
}
*/

CNode* trie::SearchForPrefix(stringsurrogate  stringsurrogate, int& Result )
{
  CNode* pNode = NULL;
  Result = 0;
   pNode = m_Root->SearchForPrefix (stringsurrogate, Result );

  return pNode;


}


//----------------------------------------------------------------
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
//
//    Get At


CNode* trie::GetRoot1()
{
  return m_Root;
}

//----------------------------------------------------------------
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
//
//    Alphabetize
void trie::Alphabetize()
{
  if ( m_IsAlphabetized == false)
  {
    m_Root->Alphabetize();
  }
  m_IsAlphabetized = true;
}

int trie::ComputeNumberOfEntries()
{
  return m_Root->ComputeNumberOfEntries(0);
}

void  trie::CreateNodeArray()
{
	// XXX. avoid delete/new cycle if there’s room
	delete[] m_NodeArray;
	m_NodeArray = new CNode*[m_NumberOfNodes];

	int Index = 0;
	m_Root->CreateNodeArray(m_NodeArray, Index);

	assert(Index = GetCount());
}


//------------------------------------------------------------------------------------
// find the deepest node in the Trie whose count is more than half of m_Count
CNode*  trie::FindLowestMajorityNode()
{
  CNode* pNode = m_Root->FindLowestMajorityNode( m_Count );

  if ( pNode == m_Root ) { return NULL; }
  else
  {
    return pNode;
  }
}



void trie::MakeAllNodesVisible(bool Flag)
{
  m_Root->MakeAllVisible(Flag);
}


bool trie::MakeVisible( const stringsurrogate string )
{
  return m_Root->MakeVisible(string);

}


//----------------------------------------------------------------//
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------//
//
//    New functions added for FSA


void trie::MakeMorphemeBoundariesAtThisWidth(int n, int MinimumStemLength)
{

  int    ThisLength = 0;
  m_Root->MakeMorphemeBoundariesAtThisWidth(n, MinimumStemLength, ThisLength);

}




//----------------------------------------------------------------//
  ////////////////////////////////////////////////////////////////
//----------------------------------------------------------------//
/*
void trie::MakeCutsAtMorphemeBoundary()
{
  int depth = 0;
  m_Root->MakeCutsAtMorphemeBoundary( depth );
}
*/

void trie::SetAutoDelete( bool b )
{
  m_AutoDelete = b;
  m_Root->SetAutoDelete(b);
}

 
//----------------------------------------------------------------
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
//
//      CNode
//----------------------------------------------------------------------------
        


CNode::CNode(string s, int StartPoint, int BreakPoint)
	: m_Key(new char[s.length()]),	// filled below
	m_KeyLength(s.length()),
	m_CorpusCount(0),
	m_Pointer(),
	m_Letters(),
	m_NumberOfBranches(0),
	m_Pointers(),
	m_CountBelow(0),
	m_Visible(false),
	m_AutoDelete(true),	// *this owns m_Pointer
	// public:
	m_StartPoint(StartPoint),
	m_BreakPoint(BreakPoint),
	m_ExistenceFlag(false),
	m_MorphemeBoundary(false)
{ LxStrCpy(s, m_Key, s.length()); }

CNode::CNode(const stringsurrogate  SS, int StartPoint, int BreakPoint)
	: m_Key(new char[SS.GetLength()]),	// filled below
	m_KeyLength(SS.GetLength()),
	m_CorpusCount(0),
	m_Pointer(),
	m_Letters(),
	m_NumberOfBranches(0),
	m_Pointers(),
	m_CountBelow(0),
	m_Visible(false),
	m_AutoDelete(true),	// *this owns m_Pointer
	// public:
	m_StartPoint(StartPoint),
	m_BreakPoint(BreakPoint),
	m_ExistenceFlag(false),
	m_MorphemeBoundary(false)
{ LxStrCpy(&SS, m_Key, SS.GetLength()); }

CNode::CNode()
	: m_Key(),
	m_KeyLength(0),
	m_CorpusCount(0),
	m_Pointer(),
	m_Letters(),
	m_NumberOfBranches(0),
	m_Pointers(),
	m_CountBelow(0),
	m_Visible(false),
	m_AutoDelete(true),	// *this owns m_Pointer
	// public:
	m_StartPoint(0),
	m_BreakPoint(0),
	m_ExistenceFlag(false),
	m_MorphemeBoundary(false) {
		std::cout << "making a node" << std::endl;
		m_Letters = NULL;
		m_Pointer = NULL;
	}

CNode::~CNode()
{
	// Delete child nodes
 	if (m_Letters != 0) {
		for (int i=0; i < m_NumberOfBranches; ++i)
			delete m_Pointers[i];
		delete[] m_Pointers;
	}
  
	// If we own it, delete data
	if (m_AutoDelete && m_Pointer)
		delete m_Pointer;
	std::cout <<"deleting a node"<<std::endl;
	delete[] m_Key;
	delete[] m_Letters;
 
}

void CNode::SetAutoDelete( bool b )
{
  m_AutoDelete = b;
  for( int i=0; m_Letters && i < m_NumberOfBranches; i++ )
  {
    m_Pointers[i]->SetAutoDelete(b);
  }
}


int	CNode::CountValidSubstrings( stringsurrogate& ss )
{
	int count = 0;

	if( m_ExistenceFlag ) count++; 
	
	CNode* pNode = FindLetter( ss[0] );
	if( pNode )
	{
		int step = pNode->m_BreakPoint - m_BreakPoint;
		stringsurrogate ssMid = ss.Mid( step );
		count += pNode->CountValidSubstrings( ssMid );
	}

	return count;
}

 
//----------------------------------------------------------------//
////////////////////////////////////////////////////////////////
//----------------------------------------------------------------//
//
//   Basic Trie functions


CNode* CNode::NodeInsert(stringsurrogate& SS, int& NumberOfNodes,
			CNode** ppNode, int* pResult)
{
	using std::auto_ptr;
	using std::copy;
	using std::swap;

	// The node that is returned is the node immediately down from
	// node that called this function in the first place.
	// It may be "This" or it may not.
	// ppNode is a pointer to the Terminal node that is eventually
	// identified or created for the string in question.
	stringsurrogate ssKey = GetKey();
	auto_ptr<CNode> this_node(this);

	// Result: 1: new node added
	//         2: node already existed

	//-----------------------------------------------------------------------//

	// 1: A difference before m_BreakPoint: it's definitely a new string.
	// should i be initialized as m_StartPoint + 1??
	int i = m_StartPoint;
	for (; i < m_BreakPoint && i < SS.GetLength(); ++i) {
		// XXX. SS and ssKey could be backwards, hence the obscure test.
//		if ( SS[i] != ssKey[i] )
		if ( LxStrCmp( &SS, ssKey.GetKey(),1,1,SS.GetStart()+i,ssKey.GetStart()+i) ) {
			// we create a new node that dominates *this and also
			// dominates the other new node created, new_node.

			auto_ptr<CNode> prev(new CNode(ssKey.Left(i), m_StartPoint, i));
			prev->GetLink(this_node.release());
			++NumberOfNodes;
			m_StartPoint = i;

			auto_ptr<CNode> new_node(new CNode(SS, i, SS.GetLength()));
			new_node->Exists();
			CNode* inserted = new_node.get();
			prev->GetLink(new_node.release());
			++NumberOfNodes;

			*ppNode = inserted;

			// Declare success.
			if (pResult) *pResult = 1;

			prev->SetCountBelow((m_ExistenceFlag ? 0 : 1) + m_CountBelow + 1);
			prev->SetCorpusCount(m_CorpusCount + 1);
			inserted->SetCorpusCount(1);

			prev->SetAutoDelete(m_AutoDelete);
			inserted->SetAutoDelete(m_AutoDelete);

			return prev.release();
		}
	}
	// Now i == m_BreakPoint or i == SS.GetLength(),
	// and m_Key[j] == SS.m_Key[j] for all j < i

	//-----------------------------------------------------------------------//

	// 2. "s" is shorter than this node's Key:
	if (i < m_BreakPoint && i == SS.GetLength()) {
		auto_ptr<CNode> prev(new CNode(ssKey.Left(i), m_StartPoint, i));
		prev->GetLink(this_node.release());
		prev->Exists();
		++NumberOfNodes;
		m_StartPoint = i;
		*ppNode = prev.get();

		// Declare success.
		if (pResult) *pResult = 1;

		prev->SetCountBelow((m_ExistenceFlag ? 0 : 1) + m_CountBelow);
		prev->SetCorpusCount(m_CorpusCount + 1);
		prev->SetAutoDelete(m_AutoDelete);

		return prev.release();
	}

	//-----------------------------------------------------------------------//

	// 3. "s" is exactly this node's key:
	if (i == m_BreakPoint && i == SS.GetLength()) {
		if (m_ExistenceFlag)
			// Already present.
			*pResult = 2;
		else
			// Success.
			*pResult = 1;

		Exists();
		SetCorpusCount(m_CorpusCount + 1);

		*ppNode = this;

		return this_node.release();
	}

	//-----------------------------------------------------------------------//
	// 4. This node only takes us part way into the word:
	char Letter = SS[m_BreakPoint];
	for (int j = 0;  j < m_NumberOfBranches; ++j) {
		if (m_Letters[j] == Letter) {
			CNode* next = m_Pointers[j];
			int result;
			auto_ptr<CNode> new_node(next->NodeInsert(SS, NumberOfNodes,
							ppNode, &result));
			if (pResult) *pResult = result;
			m_Pointers[j] = new_node.release();

			if (result == 1)
				// new descendent
				++m_CountBelow;

			++m_CorpusCount;
			return this_node.release();
		}
	}

	//-----------------------------------------------------------------------//
	// 5. the letter at BreakPoint is new:
	auto_ptr<CNode> new_node(new CNode(SS, m_BreakPoint, SS.GetLength()));
	new_node->Exists();
	new_node->SetCorpusCount(1);
	new_node->SetAutoDelete(m_AutoDelete);
	++NumberOfNodes;
	*ppNode = new_node.get();

	int length = m_NumberOfBranches;

	// XXX. use realloc work-alike
	char* NewLetters = new char[length + 1];
	CNode** NewPointers = new CNode*[length + 1];
	copy(m_Letters, m_Letters + length, NewLetters);
	copy(m_Pointers, m_Pointers + length, NewPointers);
	NewLetters[length] = Letter;
	NewPointers[length] = new_node.release();

	swap(m_Letters, NewLetters);
	swap(m_Pointers, NewPointers);
	++m_NumberOfBranches;

	delete[] NewLetters;
	delete[] NewPointers;

	// Declare success.
	if (pResult) *pResult = 1;

	++m_CountBelow;
	++m_CorpusCount;

	return this_node.release();

	//-----------------------------------------------------------------------//
	// end ///////////////////////
}


CNode** CNode::GetLink ( const stringsurrogate s )
{
  int i;

  char c = s[m_BreakPoint];
  int length = 0;

  if (m_Letters)
  {
    length = m_NumberOfBranches;
  }
  for ( i = 0;  i < length; i++)
  {
    if (m_Letters[i] == c) return &m_Pointers[i];
  }

  char* NewLetters = new char[length + 1];
  CNode** NewPointers = new CNode*[length + 1];
  for ( i = 0; i < length; i++)
  {
    NewLetters[i] = m_Letters[i];
    NewPointers[i] = m_Pointers[i];
  }
  NewLetters[length] = c;
  m_NumberOfBranches++;
  delete m_Letters;
  m_Letters = NewLetters;
  delete m_Pointers;
  m_Pointers = NewPointers;
  m_Pointers[length] = new CNode(s, m_BreakPoint, m_BreakPoint);
  return &m_Pointers[length];
}


CNode* CNode::FindLetter (char c)
{

  int length = 0;
  if (m_Letters) { length = m_NumberOfBranches;}
  for (int i = 0;  i < length; i++)
  {
    if (m_Letters[i] == c) return m_Pointers[i];
  }

  return NULL;
}


//int CNode::GetCount() const
//{
//  return m_Count;
//}


CNode** CNode::GetLink(CNode* pNode)
{
	using std::copy;
	using std::swap;

	int length = m_NumberOfBranches;

	// case 1: pNode is terminal, has same Key as this:
	if (pNode->GetKeyLength() == m_BreakPoint)
		return 0;

	char c = pNode->GetKey()[m_BreakPoint];

	for (int i = 0;  i < length; ++i)
		if (m_Letters[i] == c)
			return &m_Pointers[i];

	// XXX. should use realloc workalike
	char* NewLetters = new char[length + 1];
	CNode** NewPointers = new CNode*[length + 1];
	copy(m_Letters, m_Letters + length, NewLetters);
	copy(m_Pointers, m_Pointers + length, NewPointers);
	NewLetters[length] = c;
	NewPointers[length] = pNode;

	swap(m_Letters, NewLetters);
	swap(m_Pointers, NewPointers);
	delete[] NewLetters;
	delete[] NewPointers;

	++m_NumberOfBranches;
	return &m_Pointers[length];
}
 

stringsurrogate CNode::GetKey()
{
  return stringsurrogate(m_Key,0,m_KeyLength );
}


void  CNode::MakeATerminalPointerArray (CNode** Array, int& Index)
{

  if (m_ExistenceFlag)
  {
    Array[ Index ] = this;
    Index++;
  }

  for (int i = 0 ; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i]->MakeATerminalPointerArray(Array, Index);
  }

}


CNode* CNode::Find1(const stringsurrogate string, bool PartialOK )
{
  if (m_Key && LxStrCmp( &string, m_Key, string.GetLength(), m_KeyLength ) == 0 && ( PartialOK || m_ExistenceFlag ) )
  {
    return this;
  }

  if( m_Key )
  {
    if( string.GetLength() < m_BreakPoint )
    {
      if( !PartialOK ) return NULL;
    }

    for( int i = m_StartPoint; i < m_BreakPoint-1; i++ )
    {
      if( string[i] != m_Key[i] )
      {
        if( PartialOK && ( i > m_StartPoint ) ) return this;
		else return NULL;
      }
    }
  }

  char c = string[m_BreakPoint];
  for ( int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    if ( c == m_Letters[i] )
    {
      return m_Pointers[i] ->Find1 (string);
    }
  }
  return NULL;
}


CNode* CNode::SearchForPrefix ( stringsurrogate& SS, int& Result, int Letterno )
{
  CNode* pNode;
  assert ( Letterno == m_StartPoint);
  if ( Letterno < m_BreakPoint-1)
  {
    for (int i = Letterno + 1; i < m_BreakPoint; i++)
    {
      if ( i == SS.GetLength() )
      {
        Result = 2;
        return this;
        // Prefix is inside of this node, however!
      }
      if ( SS[i] != m_Key[i] )
      {
        Result = 0;
        return NULL;
        // Prefix not found!
      }
    }

  }

  Letterno = m_BreakPoint;

  if ( m_Key && SS == stringsurrogate( m_Key, 0, m_KeyLength ) )
  {
    Result = 1;
    return this;
  }

  for (int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
      if ( SS[Letterno] == m_Letters[i] )
      {
        pNode = FindLetter ( SS[m_BreakPoint] );
        pNode = pNode->SearchForPrefix ( SS, Result, m_BreakPoint);
        return pNode;
      }
  }
  Result = 0;
  return NULL;
}
  
int CNode::GetWidth()
{
  int width = 0;
  if (m_ExistenceFlag) { width = 1;}

  if (m_Pointers) { return m_NumberOfBranches + width; } else {return width; }

}

namespace {
	// helper for CNode::Alphabetize
	// index_in<char>("Hello")(0) == 'H'.
	template<class T> class index_in : public std::unary_function<int, T> {
		const T* array;
	public:
		index_in(const T* v) : array(v) { }
		T operator()(int i) { return array[i]; }
	};
}

void CNode::Alphabetize()
{
 

	const int Length = m_NumberOfBranches;

	if (Length < 2)
		// nothing to do
		return;
	// insertion sort -- this lists are usually short (not true for CJK, I suppose?)
	int i;
	for (int j = 1; j < Length; j++ )
	{
		char letter = m_Letters[j];
		CNode* pointer = m_Pointers[j];
		i = j - 1;
		while ( m_Letters[i] > letter ){
			m_Letters[i+1]  = m_Letters[i];
			m_Pointers[i+1] = m_Pointers[i];
			i--;
		}
		m_Letters[i+1] = letter;
		m_Pointers[i+1] = pointer; 

	}

}

void* CNode::Get_T_Pointer()
{
  if (m_ExistenceFlag)
  {
    return m_Pointer;
  }
  else
  {
    return NULL;
  }
}


int CNode::ComputeNumberOfEntries(int count)
{
  if (m_ExistenceFlag)
  {
    count++;
  }

  for (int i = 0 ; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    count = m_Pointers[i]->ComputeNumberOfEntries(count);
  }
  return count;
}


void CNode::CreateNodeArray(CNode** NodeArray, int& Index)
{

  NodeArray[Index] = this;
  Index++;

  for (int i = 0 ; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i]->CreateNodeArray(NodeArray, Index);
  }

}
 

CNode* CNode::FindLowestMajorityNode(int Count)
{
  bool  FoundFlag = false;
  CNode*  pNode;


  for (int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    if ( m_Pointers[i]->GetCountBelow() > Count / 2 )
    {
      FoundFlag = true;
      return pNode = m_Pointers[i]->FindLowestMajorityNode( Count );
    }

  }

  if ( FoundFlag == false )
  {
    if (m_CountBelow > Count / 2 ) { return this; }
    else
    {
      return NULL;
    }
  }
  else return NULL;

}
 

void CNode::MakeAllVisible(bool Flag)
{
  m_Visible = Flag;
  for (int i = 0 ; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    m_Pointers[i]->MakeAllVisible(Flag);
  }
}


bool CNode::MakeVisible( const stringsurrogate string )
{
  if (m_Key && LxStrCmp( &string, m_Key, string.GetLength(), m_KeyLength ) == 0 && m_ExistenceFlag)
  {
    m_Visible = true;
    return true;
  }

  if (m_Key)
  {
    if ( string.GetLength() < m_BreakPoint )
    {
      return false;
    }
    for (int i = m_StartPoint; i < m_BreakPoint-1;i++)
    {
      if ( string[i] != m_Key[i] )
      {
        return false;
      }
    }
  }


  char c = string[m_BreakPoint];
  for ( int i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    if ( c == m_Letters[i] )
    {
      return m_Pointers[i] ->MakeVisible (string);
    }
  }
  return false;
}

 
bool CNode::MakeMorphemeBoundariesAtThisWidth(int n, int MinimumStemLength, int ThisLength)
{
  bool val;
  bool bLowerIsBoundary = false;
  int   KeyLen = 0;
  int  NumberOfBranches=0;
 


  if ( m_Key)
  {
    KeyLen = GetKeyLength();
    ThisLength = KeyLen;
 
  }

  NumberOfBranches = GetNumberOfBranches();

   for (int i = 0 ; m_Letters && i < NumberOfBranches; i++)
  {
    val = m_Pointers[i]->MakeMorphemeBoundariesAtThisWidth(n, MinimumStemLength, ThisLength );
    if (val) bLowerIsBoundary = true;
  }

   if ( ThisLength >= MinimumStemLength && GetWidth() >= n )
  {
    m_MorphemeBoundary = true;
  }
  else
  {
    m_MorphemeBoundary = false;
  }

  return m_MorphemeBoundary;
}
  
string trie::Display()
{
	return string( m_Root->Display( 0, m_ReverseFlag ) + "=========================" );
}

string CNode::Display( int tabs, bool ReverseFlag )
{
  string Output = " ";
  string star = "*",
      width = "  Width: ",
      lt_curly = "  {",
      rt_curly = "}",
      below = " Count below: Update software";
      //below += string("%1").arg(m_CountBelow);
       
  stringsurrogate ssKey(m_Key,0,m_KeyLength);
  int i;
  
	for( i = 0; i < tabs; i++ )
	{
		Output.append( "__" );
	}
	Output.append( " " );
	  
  if (m_Key)
  {
    Output.append ( ssKey.Display() );
    if ( ReverseFlag == true )
    {
      Output.append( " (" );
      string reverse;
      LxStrCpy_R( ssKey.Display(),reverse,ssKey.GetLength(), ssKey.GetStart() );
      Output.append( reverse + ")" );
    }
  }


  if (m_ExistenceFlag )
  {
    Output.append (star);
  }
 
  if ( m_Letters )
  {
    Output.append (lt_curly);
    Output.append ( stringsurrogate( m_Letters, 0, m_NumberOfBranches ).Display() );
    Output.append (rt_curly);
  }

 
  
  Output.append ( "\n" );

  for (i = 0; m_Letters && i < (int)m_NumberOfBranches; i++)
  {
    Output.append( m_Pointers[i]->Display( tabs+1, ReverseFlag ) );
  }
  
  return Output;
}

