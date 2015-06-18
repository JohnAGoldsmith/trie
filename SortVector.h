// Index-sorting functions
// Copyright © 2009 The University of Chicago
#ifndef SORTVECTOR_H
#define SORTVECTOR_H

// These functions are deprecated.  Better to use std::sort on a list
// of values or pointers instead.

// Sort indices according to values.

/// Output is an ordered list of the row numbers of Input, sorted by value
extern void SortVector(int* out, const double* values, int len);
extern void SortStrings(int* out, const class QStringList& values, int len);
/// Output is an ordered list of the row numbers of Input, sorted alphabetically
extern void SortLetters(int* out, const class QChar* values, int len);

#endif // SORTVECTOR_H
