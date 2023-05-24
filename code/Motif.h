// Class: SeedSet
// Used to define the seeds to construct motifs

#ifndef _SeedSet_H_
#define _SeedSet_H_

using namespace std;

#include <list>
#include "Pattern.h"
#include "Pwm.h"

class Motif
{
	private:
		list<Pattern> _list;	// The list to hold the patterns of motif
		
	public:
		int Nsites;	// The number of patterns of the motif
		int Length;	//motif length
		Pwm Prf;	// The PWM of the motif

		Motif();	// Default constructor function
		Motif(list<Pattern>);	// Constructor function based on Pattern
		~Motif();	// Destructor function
		Pattern operator [] (int);	// Get one pattern

		void Print();
};

#endif
