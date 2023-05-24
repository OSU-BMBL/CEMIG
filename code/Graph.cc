#include "Graph.h"
#include "iostream"

// Empty constructor function

Graph::Graph()
{
	//cout << "Graph Start:" << endl;
	Nodes.Clear();
}

// Constructor function

Graph::Graph(NodeList nodeset)
{
	Nodes = nodeset;
}

// Destructor function

Graph::~Graph()
{
	Nodes.Clear();
}

// Function: begin
// Used to return the beginning position

//template <class T>
//iterator Graph<T>::begin()
//{
//	return Nodes.begin();
//}

// Function: end
// Used to return the ending position

//template <class T>
//iterator Graph<T>::end()
//{
//	return Nodes.end();
//}

// Function: AddNode
// Used to add one node given node

void Graph::AddNode(Node node)
{
	Nodes.Add(node);
}

// Function: AddNode
// Used to add one node given one value

void Graph::AddNode(Vertex value)
{
	Node node(value);
	Nodes.Add(node);
}

void Graph::AddNode(Vertex value, int n)
{
	Node node(value, n);
	Nodes.Add(node);
}

// Function: AddDirectedEdge
// Used to add one directed edge

void Graph::AddDirectedEdge(Node from, Node to, int cost)
{
	//(*from.Neighbors()).Add(to);
	from.AddNeighbors(to);
	//from.Weight().push_back(cost);
	from.AddWeight(cost);
	//(*to.ReverseNeighbors()).Add(from);
	to.AddReverseNeighbors(from);
	//to.ReverseWeight().push_back(cost);
	to.AddReverseWeight(cost);
}

// Function: Clear
// Used to clear the nodes

void Graph::Clear()
{
	Nodes.Clear();
}

// Function: Contains
// Used to check whether the graph contains the value

bool Graph::Contains(Vertex value)
{
	return (Nodes.FindByValue(value).Size() > 0);
}

// Function: Remove 
// Used to remove nodes given value

bool Graph::Remove(Vertex value)
{
	Node nodeToRemove = Nodes.FindByValue(value);

	if(nodeToRemove.Size() == 0)
	{
		return false;
	}

	Nodes.Remove(nodeToRemove.Value());
	
	for(typename NodeList::iterator it = Nodes.begin(); it != Nodes.end(); it ++)
	{
		Node node = *it;
		int index = 0;

		for(list<Node>::iterator it2 = node.Neighbors().begin(); it2 != node.Neighbors().end(); it2 ++)
		{
			if ((*it2).Value() == nodeToRemove.Value())
			{
				break;
			}

			index ++;
		}

		if(index >= node.Neighbors().size())
		{
			continue;
		}

		int ct = 0;

		for(list<Node>::iterator it2 = node.Neighbors().begin(); it2 != node.Neighbors().end();)
		{
			if(ct == index)
			{
				(node.Neighbors()).erase(it2 ++);
//				(*node.Neighbors()).Remove((*it2).Value());
			}
			else
			{
				it2 ++;
			}
		}

		ct = 0;

		for(list<int>::iterator it2 = node.Weight().begin(); it2 != node.Weight().end(); )
		{
			if(ct == index)
			{
				node.Weight().erase(it2 ++);
			}
			else
			{
				it2 ++;
			}

		}
	}

	return true;
}

// Function: Size
// Used to get hte number of nodes in graph

int Graph::Size()
{
	return Nodes.Size();
}
