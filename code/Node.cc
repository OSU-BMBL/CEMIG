#include "Node.h"
#include "NodeList.h"

// Empty constructor function

Node::Node()
{
	_size = 0;
}

// Constructor function

Node::Node(Vertex data)
{
	_value = data;
	list<Node> neighbors;
	_neighbors = neighbors;
	_size = data.Size();
}

// Constructor function

Node::Node(Vertex data, int n)
{
	_value = data;
	list<Node> neighbors;
	_neighbors = neighbors;
	_size = data.Size();
	Index = n;
}

// Constructor function

Node::Node(Vertex data, list<Node> neighbors)
{
	_value = data;
	_neighbors = neighbors;
}

// Destructor function

Node::~Node()
{
	//(*_neighbors).Clear();
	//(*_reverseNeighbors).Clear();
	_neighbors.clear();
	_reverseNeighbors.clear();
	list<int>().swap(_costs);
	list<int>().swap(_reverseCosts);
}

// Function: Neighbors
// Used to return the neighbors of the node as a list

list<Node> Node::Neighbors()
{
	if(_neighbors.size() != 0)
	{
		return _neighbors;
	}
	else
	{
		list<Node> neighbors;
		_neighbors = neighbors;

		return _neighbors;
	}
}

// Function: ReverseNeighbors
// Used to return the neighbors of the node in another direction as a list

list<Node> Node::ReverseNeighbors()
{
	if(_reverseNeighbors.size() != 0)
	{
		return _reverseNeighbors;
	}
	else
	{
		list<Node> neighbors;
		_reverseNeighbors = neighbors;

		return _reverseNeighbors;
	}
}

// Function: Weight
// Used to return the costs of the edges adjacent to this node

list<int> Node::Weight()
{
	if(_costs.size() > 0)
	{
		return _costs;
	}
	else
	{
		list<int> costs;
		_costs = costs;
		return _costs;
	}
}


// Function: ReverseWeight
// Used to return the reverseCosts of the edges adjacent to this node in another direction

list<int> Node::ReverseWeight()
{
	if(!_reverseCosts.empty())
	{
		return _reverseCosts;
	}
	else
	{
		list<int> reverseCosts;
		_reverseCosts = reverseCosts;
		return _reverseCosts;
	}
}

// Function: Size
// Used to return the number of nodes to compose the vertex

int Node::Size()
{
	return _size;
}

// Function: Value
// Used to return the value to construct the Node

Vertex Node::Value()
{
	return _value;
}

// Function: Operator ==

bool Node::operator == (Node n)
{
	if(_value == n.Value())
	{
		return true;
	}

	return false;
}
//void Node::Add(Node node)
//{
	//Items.push_back(node);
//}
void Node::AddNeighbors(Node node)
{
	_neighbors.push_back(node);
}
void Node::AddReverseNeighbors(Node node)
{
	_reverseNeighbors.push_back(node);
}
void Node::AddReverseWeight(int cost)
{
	_reverseCosts.push_back(cost);
}
void Node::AddWeight(int cost)
{
	_costs.push_back(cost);
}
