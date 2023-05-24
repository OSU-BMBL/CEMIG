// Class: HammingDistanceGraph

#ifndef _HammingDistanceGraph_H_
#define _HammingDistanceGraph_H_

using namespace std;

#include <map>
#include "SortedKmers.h"
#include "Hamming.h"

class HammingDistanceGraph
{
	private:
		map<pair<int, int>, int> _edgeWeightMap;	// Save the weight in Hamming Distance Graph

	public:
		int K;	// The length of k-mers
		HammingDistanceGraph();	// Empty Constructor function
		HammingDistanceGraph(SortedKmers);	// Constructor function
		~HammingDistanceGraph();	// Destructor function
		int Weight(int, int);	// The weight of an edge in Hamming Distance Graph
		void Print();	// Print the Hamming distance graph

		SortedKmers SortedK;	// The sorted k-mers
};

#endif
