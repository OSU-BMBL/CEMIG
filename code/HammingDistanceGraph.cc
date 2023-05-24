#include "HammingDistanceGraph.h"
#include "iostream"

// Empty constructor function

HammingDistanceGraph::HammingDistanceGraph() 
{
	//cout << "HammingDistanceGraph Start:" << endl;
	K = 6;
}

// Constructor function

HammingDistanceGraph::HammingDistanceGraph(SortedKmers sortedkmers)
{
	K = sortedkmers.K;
	list<Locations> K2 = sortedkmers.GetK2();

	for (list<Locations>::iterator it = K2.begin(); it != K2.end(); it ++)
	{
		for (list<Locations>::iterator it2 = K2.begin(); it2 != K2.end(); it2 ++)
		{
			if ((*it).Integer == (*it2).Integer)
			{
				continue;
			}

			pair<int, int> KmerPair;

			if((*it).Integer > (*it2).Integer)
			{
				KmerPair = make_pair((*it).Integer, (*it2).Integer);
			}
			else
			{
				KmerPair = make_pair((*it).Integer, (*it2).Integer);
			}

			Hamming a;
			
			_edgeWeightMap[KmerPair] = a.CalculateHamming((*it).Integer, (*it2).Integer);
		}
	}

	SortedK = sortedkmers;
}

// Destructor function

HammingDistanceGraph::~HammingDistanceGraph()
{}

// Function: Weight 
// Used to calculate the weight of one edge

int HammingDistanceGraph::Weight(int kmer1, int kmer2)
{
	pair<int, int> KmerPair;

	if (kmer1 > kmer2)
	{
		KmerPair = make_pair(kmer1, kmer2);
	}
	else
	{
		KmerPair = make_pair(kmer2, kmer1);
	}

	return _edgeWeightMap[KmerPair];
}

// Function: Print
// Used to print the Hamming distance graph

void HammingDistanceGraph::Print()
{
	AcgtExtensions a;
	int top = 100;
	int i = 0;

	for (map<pair<int, int>, int>::iterator it = _edgeWeightMap.begin(); it != _edgeWeightMap.end(); it ++)
	{
		if (i == top)
		{
			break;
		}

		cout << a.ToAcgtString(((it -> first).first), K) << " " << a.ToAcgtString(((it -> first).second), K) 
			<< " " << it -> second << "\n";

		i ++;
	}
}
