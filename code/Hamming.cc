#include "Hamming.h"
#include "iostream"

// Function: HammingCode
// Used to transform the integer to Hamming format

int Hamming::HammingCode(int input)
{
	// cout << "Hamming Start:" << endl;
	int count = 0;

	while (input > 0)
	{
		if ((input & 3) > 0)
		{
			count ++;
		}

		input >>= 2;
	}

	return count;
}

// Function: CalculateHamming
// Used to calculate the Hamming Distance between two k-mers in integer format

int Hamming::CalculateHamming(int kmer1, int kmer2)
{
	return HammingCode(kmer1 ^ kmer2);
}
