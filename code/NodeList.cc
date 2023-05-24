#include "NodeList.h"
//#include "Node.h"

// Constructor funciton

NodeList::NodeList() {}

// Constructor function to construct a NodeList having fixed length

NodeList::NodeList(int length)
{
	cout << "NodeList Start:" << "\n";
	for(int i = 0; i < length; i ++)
	{
		Node node;
		Items.push_back(node);
	}
	cout << "NodeList END:" << "\n";
}

// Desutrctor function

NodeList::~NodeList()
{
	list<Node>().swap(Items);
}

// Function begin
// Used to define the beginning position

//template<class T>
//iterator NodeList<T>::begin()
//{
//	return Items.begin();
//}

// Function: end
// Used to define the ending position

//iterator NodeList<T>::end()
//{
//	return Items.end();
//}

// Function: Clear
// Used to clear all the nodes in the list

void NodeList::Clear()
{
	Items.clear();
}

// Function: FindByValue
// Used to find a Node given its value

Node NodeList::FindByValue(Vertex value)
{
	typename list<Node>::iterator pos = find(Items.begin(), Items.end(), value);

	return *pos;
}

// Function: Remove
// Used to remove the node corresponding to the given value

void NodeList::Remove(Vertex value)
{
	Node node(value);
	Items.remove(node);
}

// Function: Add
// Used to add one node given the value

void NodeList::Add(Vertex value)
{
	Node node(value);
	Items.push_back(node);
}

// Function: Add
// Used to add one node given the node

void NodeList::Add(Node node)
{
	Items.push_back(node);
}

// Function: Size
// To count the number of nodes

int NodeList::Size()
{
	return Items.size();
}
