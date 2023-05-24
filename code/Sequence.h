// Class: Sequence used to hold one sequence (chrosome, P-value, sequence string, ...)

#ifndef _Sequence_H_
#define _Sequence_H_

// Maybe some functiosn should be changed into private ones.

using namespace std;

#include <string>
#include <string.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "AcgtExtensions.h"

class Sequence
{
	public:
		string Chrom;	// The chromosome
		int ChromStart;	// The start position on chromosome
		int ChromEnd;	// The end position on chromosome
		string Name;	// The name of this peak or scaffold
		int Peak;	// I don't know???
		double Pvalue;	// The signal P-value in logarithm version
		double Qvalue;	// The signal q-value in logarithm version
		int Score; 	// The score meaasuring how dark the peak is displayed
		double SignalValue;	// The average enrichment score
		char Strand;	// The strand on chromosome
		string String;	// Sequence or scaffold
		string Info;

		Sequence();	// Default constructor function
		Sequence(string, string, string);	// Constructor function
		~Sequence();	// Destructor function
		int Length();	// The length of the sequence
		int operator[](int);	// Overload the [] operator
		void Print();	// Print the basic information of the sequence
		string replaceAWithX(string, string, string);
};

#endif
