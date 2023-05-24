// Class: SortedKmers
// Used to save the sorted k-mers

#ifndef _SortedKmers_H_
#define _SortedKmers_H_

#include <list>
#include <math.h>
#include "Locations.h"
#include "AllPossibleKmers.h"

using namespace std;

class SortedKmers
{
	private:
		list<Locations> _list;	// The list of locations
		int _t;	

	public:
		SortedKmers();	// Empty construcor function
		int K;	// The length of k-mers
//		SortedKmers(AllPossibleKmers);	// Constructor function
		SortedKmers(AllPossibleKmers, int t = 100);	// Constructor function
		~SortedKmers();	// Destructor function
		list<Locations> GetK1();	// Get the top-K1 elements
		list<Locations> GetK2();	// Get the top-K2 elements
		list<Locations> GetK3();	// Get the bottom-K3 elements
		int Size();	// Return the size of list

		list<Locations> List();
};

#endif
