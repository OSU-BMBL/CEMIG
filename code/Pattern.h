// Class: Pattern
// to define the motif patterns

#ifndef _Pattern_H_
#define _Pattern_H_

using namespace std;

#include <string>
#include "Location.h"
#include "SequenceSet.h"

class Pattern
{
	public:
		int Sequence;
		int Begin;
		int End;
		int Length;
		string Str;
		bool Strand;

		Pattern(SequenceSet, Location, int, int, int);	// Constructor function
		~Pattern();	// Destructor function
		string PrintMotif(SequenceSet, Location, int, int, int);	// Print the motif string
		string GetRev(string);	// Get the reverse string of current string
};

#endif
