// Class: Graph
// Used to define digraph

#ifndef _Graph_H_
#define _Graph_H_

using namespace std;

#include <vector>
#include "DeBruijnGraph.h"
#include "Node.h"
#include "NodeList.h"
#include "Vertex.h"

class Graph
{
	public:
		Graph();	// Empty constructor function
		Graph(NodeList);	// Constructor function
//		Graph(vector<T>, int, DeBruijnGraph);	// Constructor function
		~Graph();	// Destructor function
		NodeList Nodes;	// The list of nodes
		typedef typename NodeList::iterator iterator;
		typedef typename NodeList::const_iterator const_iterator;
		iterator begin() {return Nodes.begin(); };
		iterator end() {return Nodes.end(); };

		void AddNode(Node);	// Add one node given the node
		void AddNode(Vertex);	// Add one node given the value
		void AddNode(Vertex, int);	// Add one node given the value

		void AddDirectedEdge(Node, Node, int);	// Add one edge
		void Clear();	// Clear the Graph
		bool Contains(Vertex);	// Check whether the graph contains the value
		bool Remove(Vertex);	// Remove one value
//		NodeList<T> Nodes();	// Get the node list
		int Size();	// Get the size of graph
};

#endif
