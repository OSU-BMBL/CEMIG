// Class: Hamming
// Used to define the routine functions concerning Hamming distance

#ifndef _Hamming_H_
#define _Hamming_H_

using namespace std;

class Hamming
{
	private:
		int HammingCode(int);	// To transform an integer into another coding scheme
	

	public:
		int CalculateHamming(int, int);	// To calculate the Hamming distance between two k-mers
		// coded using integer
};

#endif
