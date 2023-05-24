// Class: GraphBuilder
// Used to construct graphs of different types

#ifndef _GraphBuilder_H_
#define _GraphBuilder_H_

using namespace std;

#include "SequenceSet.h"
#include "DeBruijnGraph.h"
#include "HammingDistanceGraph.h"
#include "SortedKmers.h"
#include "AllPossibleKmers.h"
#include "MarkovModelMatrix.h"
#include "Struct.h"

class GraphBuilder
{
	public:
		DeBruijnGraph DBGraph;	// The De Bruijn graph
		HammingDistanceGraph HDGraph;	// The Hamming distance graph
		SortedKmers SortedK;	// The sorted k-mers
		AllPossibleKmers AllPossibleK;	// All possible k-mers
		MarkovModelMatrix MarkovModelM;	// Markov model matrix

		GraphBuilder();	// Default constructor function
		GraphBuilder(SequenceSet);	// Constructor function
		~GraphBuilder();	// Destructor function
		void Print();	// Print the graph onto screen
};

#endif
