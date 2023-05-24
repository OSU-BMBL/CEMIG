#include "DeBruijnGraph.h"
#include "iostream"

// Empty constructor function

DeBruijnGraph::DeBruijnGraph()
{
	//cout << "DeBruijnGraph Start:" << endl;
	K = 7;
}

// Constructor function

DeBruijnGraph::DeBruijnGraph(AllPossibleKmers AllPossibleK)
{
	_kmerList = AllPossibleK.EdgeKmers();
	K = AllPossibleK.K + 1;
}

// Destructor function

DeBruijnGraph::~DeBruijnGraph()
{}

// The edge weight

int DeBruijnGraph::Weight(int Head, int Tail)
{
	int i = Head & ((1 << (K * 2 - 2)) - 1);
	int j = Tail >> 2;

	if(i != j)
	{
		return 0;
	}

	int All = (Head << 2) | Tail;

	return _kmerList[All];
}

// Function: Print

void DeBruijnGraph::Print()
{
	AcgtExtensions a;

	for(map<int, int>::iterator it = _kmerList.begin(); it != _kmerList.end(); it ++)
	{
		cout << a.ToAcgtString(it -> first, K) << " " << a.ToAcgtString((it -> first), K).substr(0, K - 1)
			<< " " << a.ToAcgtString((it -> first), K).substr(1, K - 1) << " " << it -> second << "\n";
	}
}
