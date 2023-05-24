// Class: MarkovModelMatrix
// Used to generate Markov Model

#ifndef _MarkovModelMatrix_H_
#define _MarkovModelMatrix_H_

using namespace std;

#include <string>
#include <vector>
#include <iostream>
#include "SequenceSet.h"
#include "AcgtExtensions.h"

class MarkovModelMatrix
{
	private:
		int K = 3;	// The order
		int AllCount = 1 << (2 * K);	// The total number of K-mers
		int Mask = AllCount - 1;	// Used to claculate the reverse complementary K-mer
		double _frq[64];
		double F[4];
		double G[16];
		double H[64];
		void PrintF();
		void PrintG();
		void PrintH();

	public:
		void Sequence2Matrix(SequenceSet);	// Construct matrices from sequence set
		void String2Matrix(vector<string>);	// Construct matrices from string vector

		MarkovModelMatrix();	// Empty constructor function
		MarkovModelMatrix(SequenceSet);	// COnstructor function
		MarkovModelMatrix(string);	// Constructor function from a single sequence
		MarkovModelMatrix(string*);	// COnstructor function from sequence array
		MarkovModelMatrix(vector<string>);	// Constructor function from sequence vector
		~MarkovModelMatrix();	// Destructor function
		double operator [] (int);	// Get the element given the index
		double GetOccurrenceInRandomData(int, int, int);	// Get occurrence in random data
		void Print();
		double MatrixF(int);
		
		SequenceSet Nsequences;	// All the sequences
};

#endif
