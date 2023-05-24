// Class: Location
// Used to define one location of a k-mer

#include <iostream>

#ifndef _Location_H_
#define _Location_H_

using namespace std;

class Location
{
	public:
		int Sequence;
		int Position;
		bool Strand;

		Location(int, int, bool);	// Constructor function
		~Location();	// Destructor function

		bool operator == (const Location);	// operator ==
};

#endif
