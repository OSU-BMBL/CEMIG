// Class: Locations
// Used to define the set of locations of k-mers in dataset

#ifndef _Locations_H_
#define _Locations_H_

using namespace std;

#include <list>
#include <string>
#include <math.h>
#include "Location.h"
#include "AcgtExtensions.h"
#include "Parameter.h"
#include "PoissonEvaluator.h"

class Locations
{
	private:
		list<Location> _list;	// List of Locations
		int _ultimateNumber = 42;	// In case of overflow

	public:
		Locations();	// Empty constructor function
		Locations(int);	// Constructor function
		~Locations();	// Destructor function
		string Key(int);	// return the string corresponding to the integer
		int OccurrenceInInputData = _list.size();	// Return the occurrence in input data
		double OccurrenceInRandomData;	// Return the occurrence in random data
		int Integer;	// The integer to encode the k-mer
		
		double Pvalue;	// The P-valuye of the k-mer
		double NegLogPval;	// The negative logarithm of P-value
		int Size();	// The number of the locations
		void Add(Location);		// Add one location
		void UpdateOccurrenceInRandomData(double);	// Update the occurrence in random data
		void UpdatePval();	// Update the P-value
		typedef list<Location>::iterator iterator;
		typedef list<Location>::const_iterator const_iterator;
		iterator begin() {return _list.begin(); };
		iterator end() {return _list.end(); };
		bool operator == (const Locations);	// Comparison
};

#endif
