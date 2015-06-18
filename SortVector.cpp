// Implementation of index-sorting functions
// Copyright © 2009 The University of Chicago
#include "SortVector.h"
#include "Utility" 
#include <cstdlib>
#include <QStringList>
#include <QString>
 
#include "Stem.h"

bool stemlessthan(const pair<CStem*, double> pair1, const pair<CStem*, double> pair2 )
{
    return pair2.second < pair1.second;
}

namespace {
using std::qsort;

// compare Pair* objects.

int GreaterThan (const void *pA, const void *pB)
{
  struct Pair
  {
    int    Index;
    double  Value;
  };

	Pair F1 = *static_cast<const Pair*>(pA);
	Pair F2 = *static_cast<const Pair*>(pB);

  if ( F1.Value == F2.Value ) { return 0; }
  if ( F1.Value >  F2.Value )  { return -1; }
  return 1;
}

int FollowsAlphabetically(const void *pA, const void *pB)
{
  struct Pair
  {
    int      Index;
    QString  Value;
  };

	Pair F1 = *static_cast<const Pair*>(pA);
	Pair F2 = *static_cast<const Pair*>(pB);

  if ( F1.Value == F2.Value ) { return 0; }
  if ( F1.Value >  F2.Value )  { return -1; }
  return 1;

}

int Precedes(const void *pA, const void *pB)
{
  struct Pair
  {
    int    Index;
    char  Value;
  };

	Pair F1 = *static_cast<const Pair*>(pA);
	Pair F2 = *static_cast<const Pair*>(pB);

  if ( F1.Value == F2.Value ) { return 0; }
  if ( F1.Value <  F2.Value )  { return -1; }
  return 1;
}
}

void SortVector(int* Output, const double* Input, int Length)
{
  int i;
  struct Pair
  {
    int    Index;
    double  Value;
  };
  Pair* Pairs = new Pair[ Length ];
  for ( i = 0; i < Length; i++)
  {
    Pairs[i].Index = i;
    Pairs[i].Value = Input[i];
  }
  qsort( Pairs, Length, sizeof( Pair ), GreaterThan );
  for ( i = 0; i < Length; i++)
  {
    Output[i] = Pairs[i].Index;
  }

  delete [] Pairs;
  return;
}

void SortStrings (int* Output, const QStringList& Input, int Length)
{
  int i;
  struct Pair
  {
    int      Index;
    QString  Value;
  };
  Pair* Pairs = new Pair[ Length ];
  for ( i = 0; i < Length; i++)
  {
    Pairs[i].Index = i;
    Pairs[i].Value = Input[i];
  }
  qsort ( Pairs, Length, sizeof( Pair ), FollowsAlphabetically );
  for ( i = 0; i < Length; i++)
  {
    Output[i] = Pairs[i].Index;
  }

  delete [] Pairs;
  return;
}

void SortLetters (int* Output, const QChar* Input, int Length)
{
  int i;
  struct Pair
  {
    int    Index;
    QChar  Value;
  };
  Pair* Pairs = new Pair[ Length ];
  for ( i = 0; i < Length; i++)
  {
    Pairs[i].Index = i;
    Pairs[i].Value = Input[i];
  }
  qsort ( Pairs, Length, sizeof( Pair ), Precedes );
  for ( i = 0; i < Length; i++)
  {
    Output[i] = Pairs[i].Index;
  }

  delete [] Pairs;
  return;
}
