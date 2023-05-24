// Class: AllPossibleKmers
// Used to save all the k-mers

#ifndef _AllPossibleKmers_H_
#define _AllPossibleKmers_H_

using namespace std;

#include <map>
#include <string>
#include <iostream>
#include "Locations.h"
#include "SequenceSet.h"
#include "MathBasis.h"
#include "MarkovModelMatrix.h"
#include "Global.h"

class AllPossibleKmers
{
	private:
		map<int, Locations> _shortKmers;	// Used to save k-mers
		map<int, Locations> _longerKmers;	// Used to save k-mers
		map<int, int> _longKmers;	// Used to save (k + 1)-mers

		int String2Int(string);	// Transform strings int ointegers
		void UpdateOccurrence();	// Update the occurrence
		void UpdatePosition(SequenceSet);	// Update the positions
		void SegmentsAdd(int, Location);	// Add one segment
		
	public:
		int K;	// Length
		int ValueCount;	// The number of key-value pairs
		MarkovModelMatrix MarkovModelM;
		map<int, int> EdgeKmers();
		void PrintNodes();	// Print the short k-mers
		void PrintEdges();	// Print the long (k + 1)-kmers
		
		AllPossibleKmers();	// Empty constructor function
		AllPossibleKmers(SequenceSet, MarkovModelMatrix, int k = 6);	// Constructor function
		~AllPossibleKmers();	// Destructor function
		list<Locations> SortP();	// Sort the Locations according to the P-values
		Locations operator [](string);	// Get the locations of one k-mer
		list<Locations> Values();	// Get all the values
		list<int> Keys();	// Get all the keys
		Locations operator [] (int);	// Get the locations of one k-mer or add one
		int Size();	// Get the number of k-mers
};

#endif
