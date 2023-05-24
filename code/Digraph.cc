#include "Digraph.h"
#include "HammingGraphCluster.h"
#include "Locations.h"
#include "iostream"

// Function: ConstructDiG
// Used to construct digraph

Graph Digraph::ConstructDiG(HammingGraphCluster c, int k, DeBruijnGraph dbg)
{	
	
//	cout << "Digraph Start:" << endl;
	Graph graph;
	int length = 1 << (k * 2);
	Vertex *box = new Vertex [length];
	
	int index = 0;

	for(HammingGraphCluster::iterator it = c.begin(); it != c.end(); it ++)
	{
		Vertex vertex(*it);

		//cout << "vertex:" << vertex.Size() << "\n";
		//for(Vertex::iterator it2 = vertex.begin(); it2 != vertex.end(); it2 ++)
		//{
			//cout << "it2:" << (*it2).Size() << "\n";
		//}

		//Node node;
		graph.AddNode(vertex, index);
		index ++;

		for(vector<Locations>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2 ++)
		{
			box[(*it2).Integer] = vertex;
		}
	}
	
	for(int i = 0; i < length; i ++)
	{
		if(box[i].Size() > 0)
		{
			Locations loc(i);
			Vertex vertex(loc);

			//cout << "vertex:" << vertex.Size() << "\n";
			//for(Vertex::iterator it2 = vertex.begin(); it2 != vertex.end(); it2 ++)
			//{
				//cout << "it2:" << (*it2).Size() << "\n";
			//}

			graph.AddNode(vertex, index);
			index ++;
			box[i] = vertex;
		}
	}

	for(Graph::iterator it = graph.begin(); it != graph.end(); it ++)
	{
		for(Graph::iterator it2 = graph.begin(); it2 != graph.end(); it2 ++)
		{
			if((*it).Value() == (*it2).Value())
			{
				continue;
			}
			int w = Weight((*it).Value(), (*it2).Value(), dbg);
			if ( w > 0)
			{
				//graph.AddDirectedEdge(*it, *it2, w);
				(*it).AddNeighbors(*it2);
				(*it).AddWeight(w);
				(*it2).AddReverseNeighbors(*it);
				(*it2).AddReverseWeight(w);
			}			
		}
	}

	delete[] box;
	
	if (DEBUG)
	{
    	ofstream fout;
    	if(access("./Debug/Diagraph",F_OK) == 0) remove("./Debug/Diagraph");
    	fout.open("./Debug/Diagraph",ios::app);
    	
    	fout << "Diagraph Nodes: \n\n";
    	for(Graph::iterator it = graph.begin(); it != graph.end(); it ++)
    	{	
    		Node node = (*it);
    		Vertex vertex = (*it).Value();
    		fout << node.Index + 1 << "\t";
    		
    		for (list<Locations>::iterator it2 = vertex.begin(); it2 != vertex.end(); it2 ++)
    		{
    			Locations n = *it2;
    			fout << n.Key(6).substr(0,6) << "\t";
    		}
    		fout << "To " << (node.Neighbors()).size() << " nodes: ";
    		list<Node> Neighbors = node.Neighbors();
    		for (list<Node>::iterator it2 = Neighbors.begin(); it2 != Neighbors.end(); it2 ++)
    		{
    			Node n = *it2;
    			fout << n.Index + 1 << "; ";
    		}
    		fout << "From " << (node.ReverseNeighbors()).size() << " nodes: ";
    		list<Node> ReverseNeighbors = node.ReverseNeighbors();
    		for (list<Node>::iterator it2 = ReverseNeighbors.begin(); it2 != ReverseNeighbors.end(); it2 ++)
    		{
    			Node n = *it2;
    			fout << n.Index + 1 << "; ";
    		}
    		fout << "\n";
    	}
    	fout << "\n";
    	fout.close();
	}
	
	return graph;
}

// Function: Weight
// Used to calculate the weight between two vertices

int Digraph::Weight(Vertex v1, Vertex v2, DeBruijnGraph dbg)
{
	int sum = 0;

	for(Vertex::iterator it = v1.begin(); it != v1.end(); it ++)
	{
		for(Vertex::iterator it2 = v2.begin(); it2 != v2.end(); it2 ++)
		{
			sum += dbg.Weight((*it).Integer, (*it2).Integer);
		}
	}

	return sum;
}
