#include "HammingGraphCluster.h"
#include "Locations.h"
#include<iostream>
#include<iomanip>

// Constructor function

HammingGraphCluster::HammingGraphCluster(HammingDistanceGraph s)
{
	
	cout << "\nGet independent set in hamming distance graph started";
	fflush(stdout);
	
	vector<Locations> IndependentSet = GetIndependentNodes(s);	// Get the set of independent nodes
	
	for (int i = 0; i < IndependentSet.size(); i ++)
	{
		IndependentNodes.push_back(IndependentSet[i]);
	}
	
	uglyTime((char*)"\nGet %d independent nodes", IndependentSet.size());
//	
	cout << "\nGet clusters in hamming distance graph started";
	fflush(stdout);

	list<Locations> k2 = s.SortedK.GetK2();	// Get half the k-mers with higher significance

	int Round = 0;

	for (vector<Locations>::iterator it = IndependentSet.begin(); it != IndependentSet.end(); it ++)
	{
		
		Round = Round + 1;
		//cout << "Node "<< Round <<"/" << IndependentSet.size() << "\n";

		Locations v;	// The seed node
		v = *it;	// The seed node
		vector<Locations> c;	// The first element of the newly created list
		c.push_back(v);	// Have only one element 'v'
		vector<Locations> ng = GetNbr(k2, v, s);	// Get all hte neighbors of v and saved in a vector
		//cout << "Neighbours Size: "<< ng.size() << "\n";

		double sum = v.NegLogPval;
		double fc;
        
		ClusterEvaluator cv;
		fc = cv.Function(c, s);
        	if (ng.size() > 0)
		{
			//cout << "Cluster: "<< c.size() << "\t";
			//cout << "Fc: " << fc << "\n";
		}

        	if (ng.size() > 1)
	   	{	
			for (int i = 1; i < ng.size(); i ++)
	    		{
				for (int j = 0; j < i; j ++)
				{
					vector<Locations> newC;
                     			newC.push_back(v);
					newC.push_back(ng[i]);
					newC.push_back(ng[j]);
					
                    			double newSum = (v.NegLogPval + ng[i].NegLogPval) + (v.NegLogPval + ng[j].NegLogPval);
					if (s.Weight(ng[i].Integer, ng[j].Integer) == 1)
					{
						newSum += (ng[i].NegLogPval + ng[j].NegLogPval);
					}

					if (newSum > sum)
			    		{
						sum = newSum;
						c = newC;
					}
				}
			}
	   	}

		fc = sum * log10(c.size() + 1) / (c.size() * (c.size() - 1) + 1);

		if (ng.size() > 1)
		{
			//cout << "Cluster: "<< c.size() << "\t";
			//cout << "Fc: "<< fc << "\n";
		}

		while (ng.size() > 0)
		{
			Locations addNode;
			double addFc = 0;

			for (list<Locations>::iterator it = k2.begin(); it != k2.end(); it ++)
			{
				Locations n = *it;

				if (find(c.begin(), c.end(), n) != c.end())
				{
					continue;
				}

				double newFc = fc * (c.size() * (c.size() - 1) + 1) / log10(c.size() + 1);
				double addSum = 0; 
				for (vector<Locations>::iterator it2 = c.begin(); it2 != c.end(); it2 ++)
				{
					Locations m = *it2;
               				double w = s.Weight(n.Integer, m.Integer);
					if (w == 1)
					{
						addSum += (n.NegLogPval + m.NegLogPval);
					}
				}
			
				newFc = newFc + addSum;
				newFc = newFc * log10(c.size()+2) / (c.size() * (c.size() + 1) + 1);

                	//	cout << "newFc: "<< newFc << "\n";

				if (newFc > addFc)
				{
					addFc = newFc;
					addNode = n;
				}
			}

			if (addFc > fc)
			{	
				c.push_back(addNode);
				fc = addFc;
				//cout << "Cluster: "<< c.size() << "\t";
				//cout << "Fc: "<< fc << "\n";
			}
			else
			{
				break;
			}
		}

		map<int, int> delMap;

		for (vector<Locations>::iterator it = c.begin(); it != c.end(); it ++)
		{
			if (ng.size() < 2) 
			{
				break;
			}
			Locations n = *it;

			if (n.Integer == v.Integer)
			{
				continue;
			}

			double newFc = fc * (c.size() * (c.size() - 1) + 1) / log10(c.size() + 1);
			double delSum = 0; 
			for (vector<Locations>::iterator it2 = c.begin(); it2 != c.end(); it2 ++)
			{
				Locations m = *it2;
               			double w = s.Weight(n.Integer, m.Integer);
				//cout << "w:" << w << "\n";
				if (w == 1)
				{
					delSum += (n.NegLogPval + m.NegLogPval);
				}
			}
			
		//	cout << "newFc:" << newFc << "	";
			if (c.size() > 2) newFc = newFc - delSum;
			else if (c.size() == 2) newFc = v.NegLogPval;
			
			newFc = newFc * log10(c.size()) / ((c.size() - 1) * (c.size() - 2) + 1);

			//cout << "NewFc: " << newFc << "\t";
			//cout << "Fc: " << fc << "\t";	

			if (newFc > fc)
			{
				c.erase(it);
				//cout << "Delete " << "\t";
				//cout << "\n";
			}
			//cout << "\n";
		}

		for (vector<Locations>::iterator it = c.begin(); it != c.end();)
		{	
			if (delMap.count((*it).Integer) > 0)
			{
				c.erase(it);
			}
			else
			{
				it ++;
			}
		}

		_clusterSet.push_back(c);

		fc = cv.Function(c, s);
		
		if (Round % 5 == 0) 
		{
			verboseDot();
		}	
	}
	
	uglyTime((char*)"\nGet %d clusters", _clusterSet.size());
	
	if (DEBUG)
	{
	    	ofstream fout;
	    	if(access("./Debug/Cluster",F_OK) == 0) remove("./Debug/Cluster");
	    	fout.open("./Debug/Cluster",ios::app);
	    	
	    	fout << "Cluster: \n\n";
	    	for (int i = 0; i < _clusterSet.size(); i ++)
	    	{
	    		fout << i+1 << "\t";
	    		for (int j = 0; j < _clusterSet[i].size(); j ++)
	    		{
	    			fout << _clusterSet[i][j].Key(6).substr(0,6) << "\t";
	    		}
	    		fout << "\n";
	    	}
	    	fout << "\n";
	    	fout.close();
	}
}

// Function: GetIndependentNodes
// Used to get the set of independent nodes

vector<Locations> HammingGraphCluster::GetIndependentNodes (HammingDistanceGraph s)
{
	vector<Locations> ig;	// The set of independent nodes
	//cout << "Begin building clusters.\n";
	//cout << (s.SortedK.GetK1()).size() << "\n";

//	list<Locations> t = s.SortedK.GetK1();
//	cout << t.size() << "\n";
//	cout << (s.SortedK.GetK1()).size() << "\n";
//	int i = 0;
	list<Locations> sortedK1 = s.SortedK.GetK1();

	for (list<Locations>::iterator it = sortedK1.begin(); it != sortedK1.end(); it ++)
//	for (list<Locations>::iterator it = (s.SortedK.GetK1()).begin(); it != (s.SortedK.GetK1()).end(); it ++)
	{
//		cout << i << "\n";
		Locations segments = *it;
//		cout << "Integer: " << (*it).Integer << "\n";
//		cout << i << "\n"; 

		if (CheckIndependence (ig, segments, s))
		{
//			cout << "Add one\n";
			ig.push_back(segments);
		}
//		cout << i << "\n";
//		i ++;
//		cout << i << "\n";
	}

	return ig;
}

// Function: CheckIndependence
// Used to check whether the node set is an independent set

bool HammingGraphCluster::CheckIndependence (vector<Locations> ig, Locations s, HammingDistanceGraph G)
{
	bool flag = true;

	for (vector<Locations>::iterator it = ig.begin(); it != ig.end(); it ++)
	{
		Locations n = *it;

		if (G.Weight (n.Integer, s.Integer) < 2)
		{
			flag = false;
			break;
		}
	}
//	cout << "After\n";

//	cout << "It is: " << flag << "\n";
	return flag;
}

// Function: GetNbr

vector<Locations> HammingGraphCluster::GetNbr(list<Locations> k2, Locations v, HammingDistanceGraph s)
{
	vector<Locations> nbr;

	//cout << "GetNbr Start:\n";
	for(list<Locations>::iterator it = k2.begin(); it != k2.end(); it ++)
	{
		Locations n = *it;

		if (n.Integer == v.Integer)
		{
			continue;
		}

		if (s.Weight(v.Integer, n.Integer) < 2)
		{
			nbr.push_back(n);
		}
	}
	//cout << "GetNbr END:\n";
	return nbr;
}

// Destructor function

HammingGraphCluster::~HammingGraphCluster()
{
	for(int i = 0; i < _clusterSet.size(); i ++)
	{
		vector<Locations>().swap(_clusterSet[i]);
	}

	vector<vector<Locations> >().swap(_clusterSet);
}

// Function: Values
// Used to return all the lists of Locations in a list

//list<list<Locations> > HammingGraphCluster::Values()
//{
//	list<list<Locations> > res;
//	res.reserve(_clusterSet.size());
//
//	for(int i = 0; i < _clusterSet.size(); i ++)
//	{
//		res.push_back(_clusterSet[i]);
//	}
//
//	return res;
//}

// Function: operator []
// Used to return the element corresponding to the index

vector<Locations> HammingGraphCluster::operator [] (int id)
{
	return _clusterSet[id];
}

// Function: ToVertices
// Used to transform the clusters into vertex set

//vector<Vertex> vector<Vertex> ToVertices()
//{
//	vector<Vertex> vec;
//	vec.reserve(_clusterSet.size());
//
//	for(int i = 0; i < _clusterSet.size(); i ++)
//	{
//		Vertex vertex(_clusterSet[i]);
//		vec.push_back(vertex);
//	}
//
//	return vec;
//}

//// Function: begin
//// Used to return the beginning iterator
//
//iterator HammingGraphCluster::begin()
//{
//	return _clusterSet.begin();
//}
//
//// Function: end
//// Used to return the ending iterator
//
//iterator HammingGraphCluster::end()
//{
//	return _clusterSet.end();
//}

// 
// Function: Print
// Used to print the nodes in each cluster

int HammingGraphCluster::Size()
{
	return _clusterSet.size();
}

void HammingGraphCluster::Print()
{
	cout << "Cluster: \n";
	for (int i = 0; i < _clusterSet.size(); i ++)
	{
		cout << i+1 << "\t";
		for (int j = 0; j < _clusterSet[i].size(); j ++)
		{
			cout << _clusterSet[i][j].Key(6).substr(0,6) << "\t";
		//	cout << _clusterSet[i][j].Integer << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}

void HammingGraphCluster::PrintIndependentNodes()
{
	vector<Locations> IndependentSet = IndependentNodes;
	cout << "Independent Nodes: \n";
	cout << "Independent Nodes Size: "<< IndependentSet.size() << "\n";
	for (int i = 0; i < IndependentSet.size(); i ++)
	{
		cout << i+1 << "\t";
		cout << IndependentSet[i].Integer << "\t";
		cout << IndependentSet[i].Key(6).substr(0,6) << "\t";
		cout << IndependentSet[i].Size() << "\t";
		cout << setw(8) << IndependentSet[i].OccurrenceInRandomData << "\t";
		cout << IndependentSet[i].Pvalue << "\t";
		cout << "\n";
	}
	cout << "\n";
}
