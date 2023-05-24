// Class: Digraph
// Used to define a number of functions

#ifndef _Digraph_H_
#define _Digraph_H_

using namespace std;

#include "Graph.h"
#include "Vertex.h"
#include "DeBruijnGraph.h"
#include "HammingGraphCluster.h"
#include "Global.h"

class Digraph
{
	private:
		int Weight(Vertex, Vertex, DeBruijnGraph);
	public:
		Graph ConstructDiG(HammingGraphCluster, int, DeBruijnGraph);	// Construct digraph
};

#endif
