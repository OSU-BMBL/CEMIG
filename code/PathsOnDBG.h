// Class: PathsOnDBG
// Used to define the paths on De Bruijn Graph

#ifndef _PathsOnDBG_H_
#define _PathsOnDBG_H_

using namespace std;

#include <map>
#include <utility>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Vertex.h"
#include "Graph.h"
#include "Digraph.h"
#include "MathBasis.h"
#include "PathTuple.h"
#include "HammingGraphCluster.h"
#include "Global.h"

class PathsOnDBG
{
	private:
		vector<PathTuple> _tupleSet;	// The set of paths saved in tuple format

		pair<list<Vertex>, list<Vertex> > GetFlank(Node, int);	// Used to get the flanking strings
		pair<list<Vertex>, list<Vertex> > ReverseAndSkip(pair<list<Vertex>, list<Vertex> >);
		// Get the reverse information

		list<Vertex> Skip(list<Vertex>);	// Skip the nodes composed of single vertices
		void CoverVertices(list<Vertex>&, list<Vertex>, Vertex, list<Vertex>);
		// Cover the vertices in core area of the flanking sequence segments

	public:
		PathsOnDBG(DeBruijnGraph, HammingGraphCluster);	// Constructor function
		~PathsOnDBG();	// Destructor function
		int Size();	// The number of paths in the set
		PathTuple operator [] (int);	// Return the path tuple given index
		void Print();
};

#endif
