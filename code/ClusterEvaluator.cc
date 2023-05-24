#include "ClusterEvaluator.h"
#include "iostream"

// Function: Function
// To score a cluster saved in list<Locations> format

double ClusterEvaluator::Function(vector<Locations> cluster, HammingDistanceGraph G)
{
	//cout << "ClusterEvaluator Start:" << endl;
	double sum = 0;
	
	if (cluster.size() == 1)
	{
		sum = cluster[0].NegLogPval;
	}

	for(int i = 0; i < cluster.size() - 1; i ++)
	{
	//	cout << "i: "<< i << "\n";
		for(int j = i + 1; j < cluster.size(); j ++)
		{
		//	cout << "j: "<< i << "\n";
		//	double w = HammingDistance(cluster[i], cluster[j], G);
			double w = G.Weight(cluster[i].Integer, cluster[j].Integer);
	        	//cout << "w: "<< w << "\n";
			if (w == 1)
			{	
				sum += (cluster[i].NegLogPval + cluster[j].NegLogPval);
			}
		}
	}

	double numberOfC = cluster.size();

	return sum * log10(numberOfC + 1) / 
		(numberOfC * (numberOfC - 1) + 1);
}

// Function: HammingDistance
// To get the Hamming distance

int ClusterEvaluator::HammingDistance(Locations l1, Locations l2, HammingDistanceGraph G)
{
    double a = G.Weight(l1.Integer, l2.Integer);
    if (a == 1)
    {
    	return 1;
    }
	return 0;
}
