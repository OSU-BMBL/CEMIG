// Class: HammingGraphClusrter
// Used to represent the set of clusters obtained from Hamming Distance Graph

#ifndef _HammingGraphCluster_H_
#define _HammingGraphCluster_H_

#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include "Vertex.h"
#include "Locations.h"
#include "HammingDistanceGraph.h"
#include "ClusterEvaluator.h"
#include "Global.h"

class HammingGraphCluster
{
	private:
		vector<vector<Locations> > _clusterSet;	// The vector to save the set of clusters together with their IDs
		vector<Locations> GetIndependentNodes(HammingDistanceGraph);	// Get the independence node set
		vector<Locations> IndependentNodes;
		bool CheckIndependence(vector<Locations>, Locations, HammingDistanceGraph);	// Check whether the 
		vector<Locations> GetNbr(list<Locations>, Locations, HammingDistanceGraph);	// Get all the neighbors of current node
		// current node set is independent
		
	public:
		vector<Vertex> ToVertices();	// Transform the clustes into vertex set
		HammingGraphCluster(HammingDistanceGraph);	// Constructor function
		~HammingGraphCluster();	// Destructor function
		int Size();	
		typedef vector<vector<Locations> >::iterator iterator;
		typedef vector<vector<Locations> >::const_iterator const_iterator;
		iterator begin() {return _clusterSet.begin(); };
		iterator end() {return _clusterSet.end(); };
//		list<list<Locations> > Values();	// Get all the clusters
//		list<int> Keys();	// Get all the cluster ids
		vector<Locations> operator [] (int);	// Get the element given id
		void Print();	// Print the nodes in the cluster
		void PrintIndependentNodes();	
};

#endif
