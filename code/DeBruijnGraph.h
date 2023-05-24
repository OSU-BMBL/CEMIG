// Class: DeBruijnGraph
// Used to construct De Bruijn Graph

#ifndef _DeBruijnGraph_H_
#define _DeBruijnGraph_H_

#include<map>
#include <iostream>
#include "AllPossibleKmers.h"

using namespace std;

class DeBruijnGraph
{
	private:
		map<int, int> _kmerList;	// A map to contain the directed edges in De Bruijn Graph
	
	public:
		int K;	// The length of long k-mers

		DeBruijnGraph();	// Empty constructor function
		DeBruijnGraph(AllPossibleKmers);	// Constructor function
		~DeBruijnGraph();	// Destructor function
		int Weight(int, int);	// The edge weight
		void Print();	// Print the edges in this De Bruijn Graph
};

#endif
