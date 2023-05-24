#include "MarkovModelMatrix.h"
#include<iostream>
#include<iomanip>

// Empty constructor function

MarkovModelMatrix::MarkovModelMatrix()
{
	//cout << "MarkovModelMatrix Start:" << "\n";
	for(int i = 0; i < 4; i ++)
	{
		F[i] = 0.25;
	}

	for(int i = 0; i < 16; i ++)
	{
		G[i] = 0.25;
	}

	for(int i = 0; i < 64; i ++)
	{
		H[i] = 0.25;
		_frq[i] = 0.25;
	}
}

// Function called by constructor functions

void MarkovModelMatrix::Sequence2Matrix(SequenceSet sequences)
{
	Nsequences = sequences;
	int list[AllCount];
	int sum[AllCount / 4];
	int listF[4];
	int sumF = 0;
	int listG[16];
	int sumG[4];
	int listH[64];
	int sumH[16];

	for(int i = 0; i < 4; i ++)
	{
		listF[i] = 0;
		sumG[i] = 0;
	}

	for(int i = 0; i < 16; i ++)
	{
		sum[i] = 0;
		listG[i] = 0;
		sumH[i] = 0;
	}

	for(int i = 0; i < 64; i ++)
	{
		list[i] = 0;
		listH[i] = 0;
	}

	for (int i = 0; i < sequences.Size(); i ++)
	{
		int l = 0;
		int gx, gy, hx, hy, x, y;
		gx = 0; gy = 0; hx = 0; hy = 0; x = 0; y = 0;

		for (int j = 0; j < sequences[i].Length(); j ++)
		{
//			if(j == 0)
//			{
//				cout << listF[0] << " " << listF[1] << " " << listF[2] << " " << listF[3] << "\n";
//
//				exit(0);
//			}

			int c = sequences[i][j];

			if (c < 4)
			{
				++ l;

				// Count F;

				listF[c] ++;
				listF[c ^ 3] ++;

//				cout << listF[c] << " " << listF[c ^ 3] << "\n";

				sumF ++;

				if (l == 1)
				{
					gx = c;
					gy = ((c ^ 3) << 2);
				}

				if (l < 2)
				{
					continue;
				}

				// Count G

				gx = (((gx << 2) | c) & 15);
				gy = ((gy >> 2) | ((c ^ 3) << 2));
				listG[gx] ++;
				listG[gy] ++;
				sumG[gx >> 2] ++;
				sumG[gy >> 2] ++;

				if (l == 2)
				{
					hx = ((sequences[i][j - 1] << 2) | sequences[i][j]);
					hy = (((sequences[i][j - 1] ^ 3) << 2) | 
							((sequences[i][j] ^ 3) << 4));
					x = ((sequences[i][j - 1] << 2) | 
							sequences[i][j]);
					y = (((sequences[i][j - 1] ^ 3) << 2) | 
							((sequences[i][j] ^ 3) << 4));
				}

				if (l < 3) continue;

				// Count H

				hx = (((hx << 2) | c) & 63);
				hy = ((hy >> 2) | ((c ^ 3) << 4));
				listH[hx] ++;
				listH[hy] ++;
				sumH[hx >> 2] ++;
				sumH[hy >> 2] ++;


				if (l < K)
				{
					continue;
				}

				// Not an 'N' base

				x = (((x << 2) | c) & Mask);
				y = ((y >> 2) | ((c ^ 3) << (K * 2 - 2)));

				// We find a k-mer

				list[x] ++;
				list[y] ++;
				sum[x >> 2] ++;
				sum[y >> 2] ++;
			}
			else
			{
				// if there is an "N", restart

				l = 0;
			}
		}
	}

	
	for (int j = 0; j < 4; j ++) F[j] = (double) listF[j] / 2 / (double) sumF;


	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 4; j ++)
		{
			int index = i * 4 + j;
			int d = sumG[i];

			if (d == 0)
			{
				d = 1;
			}

			G[index] = (double) listG[index] / (double) d;
//			cout << listG[index] << ";" << d << " ";
		}
	}
//	cout << "\n";

	for (int i = 0; i < 16; i ++)
	{
		for (int j = 0; j < 4; j ++)
		{
			int index = i * 4 + j;
			int d = sumH[i];

			if (d == 0)
			{
				d = 1;
			}
			
			H[index] = (double) listH[index] / (double) d;
//			_frq[index] = (double) list[index] / (double) d;
		}
	}


	for (int i = 0; i < AllCount / 4; i ++)
	{

		for (int j = 0; j < 4; j ++)
		{
		
			int index = i * 4 + j;
			int d = sum[i];
			
			if (d == 0)
			{
				d = 1;
			}
			
			_frq[index] = (double) list[index] / (double) d;
			
		}
	
//		cout << F[0] << " " << F[1] << " " << F[2] << " " << F[3] << "\n";
	}
}

// Constructor function from sequence seet

MarkovModelMatrix::MarkovModelMatrix(SequenceSet sequences)
{
	Sequence2Matrix(sequences);
}

// Constructor function from a single sequence

MarkovModelMatrix::MarkovModelMatrix(string sequence)
{
	Sequence s("", sequence, "");
	vector<Sequence> ss(1, s);
	SequenceSet sequences(ss);
	Sequence2Matrix(sequences);
}

// String2Matrix used to construct matrices from vector of strings

void MarkovModelMatrix::String2Matrix(vector<string> VecOfStr)
{
	vector<Sequence> VecOfSeq;
	VecOfSeq.reserve(VecOfStr.size());

	for (int i = 0; i < VecOfStr.size(); i ++)
	{
		Sequence SeqOfStr("", VecOfStr[i], "");
		VecOfSeq.push_back(SeqOfStr);
	}

	SequenceSet sequences(VecOfSeq);
	Sequence2Matrix(sequences);
}

// Constructor function from vector of strings

MarkovModelMatrix::MarkovModelMatrix(vector<string> VecOfStr)
{
	String2Matrix(VecOfStr);
}

// Constructor function from array of strings

MarkovModelMatrix::MarkovModelMatrix(string* strings)
{
	int Length = sizeof(strings) / sizeof(strings[0]);
	vector<string> StringSet;
	StringSet.reserve(Length);

	for (int i = 0; i < Length; i ++)
	{
		StringSet.push_back(strings[i]);
	}

	String2Matrix(StringSet);
}

// Destructor function

MarkovModelMatrix::~MarkovModelMatrix()
{}

// Operator [] to get the element given index

double MarkovModelMatrix::operator [] (int i)
{
	return _frq[i];
}

// GetOccurrenceInRandomData

double MarkovModelMatrix::GetOccurrenceInRandomData(int key, int K, int valueCt)
{
	int k = K;
	int a[k];

	for (int i = k - 1; i >= 0; i --)
	{	
		a[i] = key & 3;
		key >>= 2;
	}

	double m = valueCt * F[a[0]] * G[a[0] * 4 + a[1]];

	for (int i = 0; i < k - 2; i ++)
	{
		int Index = a[i] * 16 + a[i + 1] * 4 + a[i + 2];
		//cout << "m: "<< m << "\n";
		//cout << "Index: "<< Index << "\n";
		//cout << "H[Index]: "<< H[Index] << "\n";
		m *= H[Index];
		//cout << "m: "<< m << "\n";
	}

	return m;
}

// PrintF

void MarkovModelMatrix::PrintF()
{
	cout << "F: " << "\n";
	cout << setw(8) << F[0] << " \t" << setw(8) << F[1] << " \t" << setw(8) << F[2] << " \t" << setw(8) << F[3] << "\n";
	cout << "\n";
}

// PrintG

void MarkovModelMatrix::PrintG()
{
	cout << "G: " << "\n";
	for(int i = 0; i < 7; i ++)
	{
		cout << setw(8) << G[i] << " \t";
	}
	cout << setw(8) << G[8] << "\n";
	for(int i = 8; i < 15; i ++)
	{
		cout << setw(8) << G[i] << " \t";
	}
	cout << setw(8) << G[15] << "\n";
	cout << "\n";
}

// PrintH

void MarkovModelMatrix::PrintH()
{
	cout << "H: " << "\n";
	for(int i = 0; i < 7; i ++)
	{
		cout << setw(8) << G[i] << " \t";
	}
	cout << setw(8) << G[8] << "\n";
	for(int i = 8; i < 15; i ++)
	{
		cout << setw(8) << G[i] << " \t";
	}
	cout << setw(8) << G[15] << "\n";
	for(int i = 16; i < 23; i ++)
	{
		cout << setw(8) << G[i] << " \t";
	}
	cout << setw(8) << G[23] << "\n";
	for(int i = 24; i < 31; i ++)
	{
		cout << setw(8) << G[i] << " \t";
	}
	cout << setw(8) << G[32] << "\n";
	for(int i = 32; i < 39; i ++)
	{
		cout << setw(8) << G[i] << " \t";
	}
	cout << setw(8) << G[39] << "\n";
	for(int i = 40; i < 47; i ++)
	{
		cout << setw(8) << G[i] << " \t";
	}
	cout << setw(8) << G[47] << "\n";
	for(int i = 48; i < 55; i ++)
	{
		cout << setw(8) << G[i] << " \t";
	}
	cout << setw(8) << G[55] << "\n";
	for(int i = 56; i < 63; i ++)
	{
		cout << setw(8) << G[i] << " \t";
	}
	cout << setw(8) << G[63] << "\n";
	cout << "\n";
}

double MarkovModelMatrix::MatrixF(int i)
{
	if (i < 4) return F[i];
	return 0;
}

// Print

void MarkovModelMatrix::Print()
{
	cout << "Markov Model Matrix: " << "\n";
	PrintF();
	PrintG();
	PrintH();
}
