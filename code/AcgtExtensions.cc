#include "AcgtExtensions.h"
#include "iostream"
// Constructor function

//AcgtExtensions::AcgtExtensions(char in)
//{
//	_char = in;
//}

// Destructor function

//AcgtExtensions::~AcgtExtensions() {}

// Function: ToAcgtString
// Used to transform integer to string

string AcgtExtensions::ToAcgtString(int x, int k)
{
//	cout << "AcgtExtensions Start:" << endl;
	char* sb;
	sb = new char [k];
	// cout << "sb: "<< sb << "\n";
	
	// cout << "x= "<< x <<"\n";

	for(int i = 0; i < k; i ++)
	{
		char c = Acgt[x % 4];
		// cout << "c: "<< c << "\n";
		sb[k -1 - i] = c;
		// cout << "sb: "<< sb << "\n";
		x >>= 2;

		// cout << "x= "<< x <<"\n";


	}
	string str(sb);

	// for (int i = 0; i < k; i++)
	// {
	//	delete[] sb[i];
	// }
	delete[] sb;

	return str;
}

// Function: ToByte
// Used to transform character into integer

int AcgtExtensions::ToByte(char c)
{
	return c < 128 ? SeqNt4Table[c] : 4;
}
