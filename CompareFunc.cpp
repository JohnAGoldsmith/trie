// Implementation of comparison and sorting functions
// Copyright © 2009 The University of Chicago
#include "CompareFunc.h"

#include <algorithm>
#include <iterator>
#include <utility>
#include <string>
#include "StringFunc.h"
#include "parse.h"

int CompareAlphabetically(const void *pA, const void *pB)
{
	
	parse* pS1 = *static_cast<parse* const*>(pA);
	parse* pS2 = *static_cast<parse* const*>(pB);

 
	return LxStrCmp( pS1->GetKeyPointer(),
					pS2->GetKeyPointer(),
					pS1->GetKeyLength(),
					pS2->GetKeyLength() );
}

int CompareReverseAlphabetically(const void *pA, const void *pB)
{
	parse* pS1 = *static_cast<parse* const*>(pA);
	parse* pS2 = *static_cast<parse* const*>(pB);

	  char* S1 = new char[pS1->GetKeyLength()];
	  char* S2 = new char[pS2->GetKeyLength()];
	  LxStrCpy_R( pS1->GetKeyPointer(), S1, pS1->GetKeyLength() );
	  LxStrCpy_R( pS2->GetKeyPointer(), S2, pS2->GetKeyLength() );
	  int comp = LxStrCmp( S1, S2, pS1->GetKeyLength(), pS2->GetKeyLength() );

	  delete [] S1;
	  delete [] S2;

	  return comp;
}
/*
int CompareSortingQuantity (const void *pA, const void *pB)
{
	parse* pS1 = *static_cast<parse* const*>(pA);
	parse* pS2 = *static_cast<parse* const*>(pB);
  	float  dif =   pS2->GetSortingQuantity() -  pS1->GetSortingQuantity();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

int CompareSortingString (const void *pA, const void *pB)
{
	parse* pS1 = *static_cast<parse* const*>(pA);
	parse* pS2 = *static_cast<parse* const*>(pB);	

  return LxStrCmp( pS1->GetSortingString(), pS2->GetSortingString(), pS1->GetSortingString().length(), pS2->GetSortingString().length() );

}

int CompareNumberOfStems (const void *pA, const void *pB)
{
	parse* pS1 = *static_cast<parse* const*>(pA);
	parse* pS2 = *static_cast<parse* const*>(pB);	
	int dif = pS2->GetNumberOfStems() -  pS1->GetNumberOfStems();

  	if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}

}

 

 
int CompareCorpusCount (const void *pM1,   const void *pM2)
{
	parse* pS1 = *static_cast<parse* const*>(pA);
	parse* pS2 = *static_cast<parse* const*>(pB);
	int dif = pS2->GetCorpusCount() -  pS1->GetCorpusCount();

  if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

 

int CompareLength (const void *pM1,   const void *pM2)
{
	parse* pS1 = *static_cast<parse* const*>(pA);
	parse* pS2 = *static_cast<parse* const*>(pB);
  	int  dif =   pS2->GetKeyLength() -  pS1->GetKeyLength();

  	if (dif > 0) {return 1;} else if (dif < 0) {return -1;} else {return 0;}
}

 */
 
 
// compare() for basic types
int MakeComparable(int a, int b)
{
	const int difference = a - b;

	if (difference < 0) return -1;
	else if (difference == 0) return 0;
	else return 1;
}

int MakeComparable(double a, double b)
{
	const double difference = a - b;

	if (difference < 0) return -1;
	else if (difference == 0) return 0;
	else return 1;
}
