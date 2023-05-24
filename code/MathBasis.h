// Class: Mathbasis
// Used to defien the basic math funcitons

#ifndef _MathBasis_H_
#define _MathBasis_H_

using namespace std;

#include <map>
#include <list>
#include <algorithm>
#include "Location.h"

#define PI 3.1415926535897932353626
#define EXTEND 3
#define MAXLEN 19
#define ALPHABET_SIZE 4
#define C1 0.5
#define C2 0.25
#define C3 1/3
#define LENGTH 6

class MathBasis
{
	private:
		int _a;
		int partition(double*, int, int, int*);	// called by quickSort

	public:
		MathBasis();	// Constructor function
		~MathBasis();	// Destructor function
		void quickSort(double*, int, int, int*);	// sort the elements in increasing order
		list<Location> Intersect(list<Location>, list<Location>);	// Get the intersection
		list<Location> Union(list<Location>, list<Location>);	// Get the union
};

#endif
