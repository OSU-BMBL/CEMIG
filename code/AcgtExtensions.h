// Class: AcgtExtensions
// Used to encode the nucleotides

#ifndef _AcgtExtensions_H_
#define _AcgtExtensions_H_

using namespace std;

#include <string>

class AcgtExtensions
{
	private:
//		char _char;	// The nucleotide
		char Acgt[4] = {'A', 'C', 'G', 'T'};
		int SeqNt4Table[128] = 
		{
			4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
			4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
			4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
			4, 1, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4,
			4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 1, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4,
			4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
		};
		
	public:
//		AcgtExtensions(char);	// Constructor function
//		~AcgtExtensions();	// Destructor function
		string ToAcgtString(int ,int);	// Transform integer into strings
		int ToByte(char);	// Transform character into integer
};

#endif
