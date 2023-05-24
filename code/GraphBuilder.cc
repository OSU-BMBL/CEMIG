#include "GraphBuilder.h"
#include "iostream"

// Default constructor function

GraphBuilder::GraphBuilder()
{
	SequenceSet ss;
	MarkovModelMatrix m(ss);
	MarkovModelM = m;

	AllPossibleKmers a(ss, MarkovModelM);
	AllPossibleK = a;

	SortedKmers s(AllPossibleK);
	SortedK = s;

	DeBruijnGraph d(AllPossibleK);
	DBGraph = d;

	HammingDistanceGraph h(SortedK);
	HDGraph = h;
}

// Constructor function

GraphBuilder::GraphBuilder(SequenceSet InputSeq)
{
	cout << "\nBuild graphs started";
	fflush(stdout);
	
	MarkovModelMatrix m(InputSeq);
	MarkovModelM = m;
	verboseDot();

	AllPossibleKmers a(InputSeq, MarkovModelM);
	AllPossibleK = a;
	verboseDot();

	SortedKmers s(AllPossibleK);
	SortedK = s;
	verboseDot();

	DeBruijnGraph d(AllPossibleK);
	DBGraph = d;
	verboseDot();

	HammingDistanceGraph h(SortedK);
	HDGraph = h;
	verboseDot();
	
	uglyTime((char*)"\nSignal of all graphs building complete");
}

// Destructor function

GraphBuilder::~GraphBuilder()
{}

// Function: Print
// To print the graph information

void GraphBuilder::Print()
{
	MarkovModelM.Print();
	AllPossibleK.PrintNodes();
	AllPossibleK.PrintEdges();
	DBGraph.Print();
	HDGraph.Print();
}
