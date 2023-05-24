// Class: ClusterEvaluator
// To score the clusters

#ifndef _ClusterEvaluator_H_
#define _ClusterEvaluator_H_

using namespace std;

#include <vector>
#include "HammingDistanceGraph.h"
#include "Locations.h"

class ClusterEvaluator
{
	public:
		double Function(vector<Locations>, HammingDistanceGraph);
		int HammingDistance(Locations, Locations, HammingDistanceGraph);
};

#endif
