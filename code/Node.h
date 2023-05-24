// CLass: Node
// Used to define the nodes in graph

#pragma once

#ifndef _Node_H_
#define _Node_H_

using namespace std;

#include <list>
#include "Vertex.h"
//#include "NodeList.h"

class NodeList;

class Node
{
	private:
		//NodeList* _neighbors;	// Neighbors of the node
		//NodeList* _reverseNeighbors;	// Neighbors of the node in another direction
		list<Node> _neighbors;
		list<Node> _reverseNeighbors;
		list<int> _costs;	// Costs of edges adjacent to this node
		list<int> _reverseCosts;	// Costs of edges adjacent to this node in another direction
		int _size;	// The number of nodes in the vertex to construct the node
		Vertex _value;	// The value to construct the node

	public:
		Node();	// Empty constructor function
		Node(Vertex);	// Constructor function
		Node(Vertex, int);	// Constructor function
		//Node(Vertex, NodeList);	// Constructor function
		Node(Vertex, list<Node>);	// Constructor function
		~Node();	// Destructor function
		
		
		//NodeList* Neighbors();	// Get the neighbors as a list
		//NodeList* ReverseNeighbors();	// Get the reverse neighbors as a list
		list<Node> Neighbors();
		list<Node> ReverseNeighbors();
		list<int> Weight();	// Get the weights of edges adjacent to this node
		list<int> ReverseWeight();	// Get the weights of edges adjacent to this node in another direction
		int Size();	// Return the number of nodes in the vertex
		Vertex Value();	// Return the value to construct the node
		bool operator ==(Node);	// Compare nodes
		//void Add(Node);	// Add one node given the node
		void AddNeighbors(Node);
		void AddReverseNeighbors(Node);
		void AddWeight(int);
		void AddReverseWeight(int);
		
		int Index;
};

#endif
