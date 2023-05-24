#include "AllPossibleKmers.h"
#include "iostream"
#include <fstream>
#include <string.h>
#include <cstring>
#include <iostream>

using namespace std;

// Empty constructor function

AllPossibleKmers::AllPossibleKmers()
{
	K = 7;
}

// Constructor function

AllPossibleKmers::AllPossibleKmers(SequenceSet s, MarkovModelMatrix m, int k)
{
	MarkovModelM = m;
	K = k;
	UpdatePosition(s);
	UpdateOccurrence();
}

// Destructor function

AllPossibleKmers::~AllPossibleKmers() {}

// Function: SortP
// Used to sort the Locations according to the P-values

list<Locations> AllPossibleKmers::SortP()
{
//	cout << "AllPossibleKmers Start:" << endl;
	list<Locations> lst;	// List of Locations to output
	double *p; int *id; Locations* l = new Locations [_shortKmers.size()];
	int size = _shortKmers.size();
	p = new double [size];
	id = new int [size];
	int i = 0;
	
	if (DEBUG)
	{
		ofstream fout;
		
		if(access("./Debug/AllKmers",F_OK) == 0) remove("./Debug/AllKmers");
		fout.open("./Debug/AllKmers",ios::app);
		
		fout << "All Kmers: \n";
		fout << "All Kmers Size: "<< _shortKmers.size() << "\n";
		for(map<int, Locations>::iterator it = _shortKmers.begin(); it != _shortKmers.end(); it ++)
		{
			Locations n = (it -> second);
			fout << n.Integer << "\t";
			fout << n.Key(6).substr(0,6) << "\t";
			fout << n.Size() << "\t";
			fout << n.OccurrenceInRandomData << "\t\t";
			fout << n.Pvalue << "\t";
			fout << "\n";
		}
		fout << "\n";
		fout.close();
	}
	
	for(map<int, Locations>::iterator it = _shortKmers.begin(); it != _shortKmers.end(); it ++)
	{
		p[i] = (it -> second).Pvalue;
		l[i] = (it -> second);
		id[i] = i;

		i ++;

	//	cout << (it -> second).Integer << "\t";
	//	cout << (it -> second).Key(6).substr(0,6) << "\t";
	//	cout << (it -> second).OccurrenceInRandomData << "\t\t";
	//	cout << (it -> second).Pvalue << "\t";
	//	cout << "\n";
	}

	MathBasis a;
	a.quickSort(p, 0, size - 1, id);

	for (i = 0; i < size; i ++)
	{
		lst.push_back(l[id[i]]);
	}

	delete [] p; delete [] id; delete [] l;

//	cout << "All Possible Kmers: \n";
//	cout << "All Possible Kmers Size: "<< lst.size() << "\n";
//	for (list<Locations>::iterator it = lst.begin(); it != lst.end(); it ++)
//	{
//		Locations n = *it;
//		cout << n.Integer << "\t";
//		cout << n.Key(6).substr(0,6) << "\t";
//		cout << n.Size() << "\t";
//		cout << n.OccurrenceInRandomData << "\t\t";
//		cout << n.Pvalue << "\t";
//		cout << "\n";
//	}
//	cout << "\n";
	
	if (DEBUG)
	{
		ofstream fout;
		
	    	if(access("./Debug/AllKmersSorted",F_OK) == 0) remove("./Debug/AllKmersSorted");
	    	fout.open("./Debug/AllKmersSorted",ios::app);
	    	
	    	fout << "All Possible Kmers: \n";
	    	fout << "All Possible Kmers Size: "<< lst.size() << "\n";
	    	for (list<Locations>::iterator it = lst.begin(); it != lst.end(); it ++)
	    	{
	    		Locations n = *it;
	    		fout << n.Integer << "\t";
	    		fout << n.Key(6).substr(0,6) << "\t";
	    		fout << n.Size() << "\t";
	    		fout << n.OccurrenceInRandomData << "\t\t";
	    		fout << n.Pvalue << "\t";
	    		fout << "\n";
	    	}
	    	fout << "\n";
	    	fout.close();
	}

	return lst;

}

// Function: String2Int
// Used to transform string into integer

int AllPossibleKmers::String2Int(string key)
{
	int x = 0;

	for(int i = 0; i < K; i ++)
	{
		AcgtExtensions a;
		int c = a.ToByte(key[i]);

		if(c >= 4)
		{
			cerr << "Error: there is an unrecognized letter!\n";
			exit(0);
		}

		x = (x << 2) | c;
	}

	return x;
}

// Function: UpdateOccurrence

void AllPossibleKmers::UpdateOccurrence()
{
	for(map<int, Locations>::iterator it = _shortKmers.begin(); it != _shortKmers.end(); it ++)
	{
		float occurrenceInRandomData = MarkovModelM.GetOccurrenceInRandomData(it -> first, this->K, this->ValueCount);
		//cout << "it -> first: "<< it -> first << "\n";
		//cout << "this->ValueCount: "<< this->ValueCount << "\n";
		//cout << "occurrenceInRandomData: "<< occurrenceInRandomData << "\n";
		(it -> second).UpdateOccurrenceInRandomData(occurrenceInRandomData);
		(it -> second).UpdatePval();
	}
}

// Function: UpdatePosition

void AllPossibleKmers::UpdatePosition(SequenceSet sequences)
{
	int mask = (1 << (2 * K)) - 1;
	int  LongMask = (1 << (2 * (K + 1))) - 1;
						
	for (int index = 0; index < sequences.Size(); index ++)
	{
		Sequence sequence = sequences[index];

		int x, y;

		x = 0;
		y = 0;
		int l = 0;

		int p, q;

		p = 0;
		q = 0;

		for (int i = 0; i < sequence.Length(); i ++)
		{
			int c = sequence[i];
			
			if (c < 4)
			{

				if (l == 0)
				{
					x = sequence[i];
					y = (sequence[i] ^ 3) << 2;

					p = sequence[i];
					q = (sequence[i] ^ 3) << 2;
				}
				
				if (l < 1)
				{
					++ l;

					continue;
				}

				// not an "N" base

				x = ((x << 2) | c) & mask;
				y = (y >> 2) | ((c ^ 3) << (K * 2 - 2));

				p = ((p << 2) | c) & LongMask;
				q = (q >> 2) | ((c ^ 3) << (K * 2));

				if (++l < K) continue;

				// we find a k-mer

				int id = i - K + 1;
				char strand = sequence.Strand;
				Location PosLoc(index, id, true);
				Location NegLoc(index, id, false);
				
				if (strand == '.') 
				{
					SegmentsAdd(x, PosLoc);
					SegmentsAdd(y, NegLoc);
				}
				if (strand == '+') SegmentsAdd(x, PosLoc);
				if (strand == '-') SegmentsAdd(y, NegLoc);

				if (l < K + 1) continue;

				if (_longKmers.count(p) > 0)
				{
					_longKmers[p] ++;
					_longKmers[q] ++;
				}
				else
				{
					_longKmers[p] = 1;
					_longKmers[q] = 1;
				}
			}
			else
			{
				l = 0;

			}
		}
	}
}

// Function: SegmentsAdd

void AllPossibleKmers::SegmentsAdd(int s, Location pos)
{
	ValueCount ++;
								
	if (_shortKmers.count(s) > 0)
	{
		_shortKmers[s].Add(pos);
	}
	else
	{
		Locations loc(s);
		loc.Add(pos);
		_shortKmers[s] = loc;
	}
}

// Function: []
// Get the corresponding value given the key

Locations AllPossibleKmers::operator [] (string s)
{
	if(s.length() != K)
	{
		cerr << "Error: The length of k-mer is wrong.\n";
		exit(0);
	}

	return _shortKmers[String2Int(s)];
}

// Function: Values
// Used to get all the values saved in a list

list<Locations> AllPossibleKmers::Values()
{
	list<Locations> ValueList;

	for(map<int, Locations>::iterator it = _shortKmers.begin(); it != _shortKmers.end(); it ++)
	{
		ValueList.push_back(it -> second);
	}

	return ValueList;
}

// Function: Keys
// Used to get all the keys saved in a list

list<int> AllPossibleKmers::Keys()
{
	list<int> KeyList;

	for(map<int, Locations>::iterator it = _shortKmers.begin(); it != _shortKmers.end(); it ++)
	{
		KeyList.push_back(it -> first);
	}

	return KeyList;
}

// Function: operator []

Locations AllPossibleKmers::operator [] (int s)
{
	if(_shortKmers.count(s) > 0)
	{
		return _shortKmers[s];
	}
	else
	{
		Locations loc(s);
		_shortKmers[s] = loc;

		return _shortKmers[s];
	}
}

// Function: Size
// Used to get the number of k-mers

int AllPossibleKmers::Size()
{
	return _shortKmers.size();
}

// Function: EdgeKmers
// To return the map of long k-mers

map<int, int> AllPossibleKmers::EdgeKmers()
{
	return _longKmers;
}

// Function: PrintNodes
// To print the short k-mers

void AllPossibleKmers::PrintNodes()
{
//	int i = 0;

	AcgtExtensions a; 
	for(map<int, Locations>::iterator it = _shortKmers.begin(); it != _shortKmers.end(); it ++)
	{
//		if(i > 10)
//		{
//			break;
//		}

//		i ++;
		cout << it -> first << " " << a.ToAcgtString(it -> first, K) << " " << (it -> second).Size() << "\n";
	}
}

// Function: PrintEdges
// To print the long (k + 1)-mers

void AllPossibleKmers::PrintEdges()
{
//	int i = 0;

	AcgtExtensions a; 

	for(map<int, int>::iterator it = _longKmers.begin(); it != _longKmers.end(); it ++)
	{
//		if(i > 10)
//		{
//			break;
//		}

//		i ++;
		cout << it -> first << " " << a.ToAcgtString(it -> first, K + 1) << " " << it -> second << "\n";
	}
}
