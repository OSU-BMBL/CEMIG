// Class: SequenceSet to hold input sequences

#ifndef _SequenceSet_H_
#define _SequenceSet_H_

using namespace std;

#include <vector>
#include <fstream>
#include <sstream>
#include "Sequence.h"
#include "Struct.h"
#include "Global.h"

class SequenceSet
{
	private:
		vector<Sequence> _sequences;	// The sequence set
		void Vector2SequenceSet(vector<Sequence>);	// transform Sequence vecor into SequenceSet
	
	public:
		SequenceSet();	// Empty constructor function
		SequenceSet(string);	// Default constructor function
		SequenceSet(vector<Sequence>);	// Constructor function
		~SequenceSet();	// Destructor function
		size_t Size();	// The number of sequences
		Sequence operator [] (int);	// Get one sequence
		static vector<Sequence> GetSequences(string);	// Read sequences into program
		void Print();	// Print the sequence information
		
		int Count(); // The number of Nucleotides
};

#endif
