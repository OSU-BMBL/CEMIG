// Class: NodeList
// Used to define the neighbors of a node

#pragma once

using namespace std;

#ifndef _NodeList_H_
#define _NoeList_H_

#include <list>
#include <algorithm>
#include "Vertex.h"
#include "Node.h"

//class Node;

class NodeList
{
	public:
		NodeList();	// Constructor function
		NodeList(int);	// Constructor function to construct a NodeList having fixed length
		~NodeList();	// Destructor function
		list<Node> Items;	// The node list

		typedef typename list<Node>::iterator iterator;
		typedef typename list<Node>::const_iterator const_iterator;
		iterator begin() {return Items.begin(); };
		iterator end() {return Items.end(); };
		void Add(Vertex);	// Add one node given the value
		void Add(Node);	// Add one node given the node
		Node FindByValue(Vertex);	// Find a value in a NodeList
		void Clear();	// Clear all the nodes in the list
		void Remove(Vertex);	// Remove the element given the value
		int Size();	// The number of nodes
};

#endif
