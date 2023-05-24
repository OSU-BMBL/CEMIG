#include "PathsOnDBG.h"

// Constructor function

PathsOnDBG::PathsOnDBG(DeBruijnGraph dbg, HammingGraphCluster c)
{
	cout << "\nGet diagraph started";
	fflush(stdout);
	
	int k = dbg.K;
	int dot = 0;
	int ii = 1;
	Digraph a;
	Graph digraph = a.ConstructDiG(c, k, dbg);	// Construct a digraph used to shrink nodes
	list<Vertex> flagMap;
	
	uglyTime((char*)"\nSignal of diagraph building complete");
	
	cout << "\nGet paths in de bruijn graph started";
	fflush(stdout);
	
	for(Graph::iterator it = digraph.begin(); it != digraph.end(); it ++)
	{
		dot ++;
		if (dot >= ii*digraph.Size()/10) 
		{
			verboseDot();
			ii++;
		}
		
		Vertex vertex = (*it).Value();
		Node node = *it;
		
		if(vertex.Size() == 1)
		{
			continue;
		}

		if(find(flagMap.begin(), flagMap.end(), vertex) != flagMap.end())
		{
			continue;
		}
		pair<list<Vertex>, list<Vertex> > flkSeq = GetFlank(node, k);	// Determine the bordiers of the motif sequences
		pair<list<Vertex>, list<Vertex> > flkSeqAndRev = ReverseAndSkip(flkSeq);// Add the complementary sequences
		CoverVertices(flagMap, flkSeqAndRev.first, vertex, flkSeqAndRev.second);	// Cover the vertices in core area
		PathTuple tuple = {.Left = flkSeqAndRev.first, .Center = vertex, .Right = flkSeqAndRev.second };
		// Save the current tuple
		
		_tupleSet.push_back(tuple);

	}
	
	uglyTime((char*)"\nGet %d paths", _tupleSet.size());
	
	if (DEBUG)
	{
	    	ofstream fout;
	    	if(access("./Debug/Paths",F_OK) == 0) remove("./Debug/Paths");
	    	fout.open("./Debug/Paths",ios::app);
	    	
	    	fout << "Paths On DBG: \n\n";
	    	for (int i = 0; i < _tupleSet.size(); i ++)
	    	{
	    		fout << "Path " << i+1 << " :\n\n";
	    		int j = 0;
	    		
	    		list<Vertex> lv = _tupleSet[i].Left;
	    		for (list<Vertex>::iterator it = lv.begin(); it != lv.end(); it++)
	    		{
	    			fout << j+1 << "\t";
	    			Vertex n = *it;
	    			for (list<Locations>::iterator it2 = n.begin(); it2 != n.end(); it2++)
	    			{
	    				Locations m = *it2;
	    				fout << m.Key(6).substr(0,6) << "\t";
	    			}
	    			fout << "\n";
	    			j++;
	    		}
	    		
	    		fout << j+1 << "*" << "\t";
	    		Vertex cv = _tupleSet[i].Center.Value();
	    		for (list<Locations>::iterator it = cv.begin(); it != cv.end(); it++)
	    		{
	    			Locations n = *it;
	    			fout << n.Key(6).substr(0,6) << "\t";
	    		}
	    		fout << "\n";
	    		j++;
	    			
	    		list<Vertex> rv = _tupleSet[i].Right;
	    		for (list<Vertex>::iterator it = rv.begin(); it != rv.end(); it++)
	    		{
	    			fout << j+1 << "\t";
	    			Vertex n = *it;
	    			for (list<Locations>::iterator it2 = n.begin(); it2 != n.end(); it2++)
	    			{
	    				Locations m = *it2;
	    				fout << m.Key(6).substr(0,6) << "\t";
	    			}
	    			fout << "\n";
	    			j++;
	    		}
	    	}
	    	fout << "\n";
	    	fout.close();
	}
}

// Function: GetFlank
// Used to get the left and right flanking sequences

pair<list<Vertex>, list<Vertex> > PathsOnDBG::GetFlank(Node vertex, int k)
{
	list<Vertex> l, r;	// The two list to hold the nodes on the left and right
	Node left = vertex;
	Node right = vertex;
	int leftFlag = 0;
	int rightFlag = 0;

	for(int i = 0; i < MAXLEN - k; i ++)
	{
		Node maxNeighbor, maxReverseNeighbor;
		int maxIndex, maxReverseIndex, id;
		int maxWeight, maxReverseWeight;

		maxIndex = -1;
		maxWeight = -1;
		id = 0;
		
		list<int> rw = right.Weight();
		list<Node> rn = right.Neighbors();
		list<int> lw = left.ReverseWeight();
		list<Node> ln = left.ReverseNeighbors();
		
		if (rw.size() > 0)
		{
			for(list<int>::iterator it = rw.begin(); it != rw.end(); it ++)
			{
				if(*it > maxWeight)
				{
					maxIndex = id;
					maxWeight = *it;
				}
	
				id ++;
			}
		}

		id = 0;

		if (rn.size() > 0)
		{
			for(list<Node>::iterator it = rn.begin(); it != rn.end(); it ++)
			{
				if(id == maxIndex)
				{
					maxNeighbor = *it;
					break;
				}
	
				id ++;
			}
		}

		maxReverseIndex = -1;
		maxReverseWeight = -1;
		id = 0;
		
		if (lw.size() > 0)
		{
			for(list<int>::iterator it = lw.begin(); it != lw.end(); it ++)
			{
				if(*it > maxReverseWeight)
				{
					maxReverseIndex = id;
					maxReverseWeight = *it;
				}
	
				id ++;
			}
		}

		id = 0;

		if (ln.size() > 0)
		{
			for(list<Node>::iterator it = ln.begin(); it != ln.end(); it ++)
			{
				if(id == maxReverseIndex)
				{
					maxReverseNeighbor = *it;
					break;
				}
				
				id ++;
			}
		}

		if (maxWeight == -1 && maxReverseWeight == -1) break;
		if(maxWeight >= maxReverseWeight)
		{
			if(maxNeighbor.Size() == 1)
			{
				rightFlag ++;
				leftFlag = 0;
			}

			if(rightFlag == 3)
			{
					break;
			}

			r.push_back(maxNeighbor.Value());
			right = maxNeighbor;
		}
		else
		{
			if(maxReverseNeighbor.Size() == 1)
			{
				leftFlag ++;
				rightFlag = 0;
			}

			if(leftFlag == 3)
			{
					break;
			}

			l.push_back(maxReverseNeighbor.Value());
			left = maxReverseNeighbor;
		}
	}
	return (make_pair(l, r));
}

// Function: ReverseAndSkip
// Used to add the reverse relationships onto the path

pair<list<Vertex>, list<Vertex> > PathsOnDBG::ReverseAndSkip(pair<list<Vertex>, list<Vertex> > p)
{
	list<Vertex> lRev = p.first;
	list<Vertex> rRev = p.second;
	reverse(lRev.begin(), lRev.end());
	reverse(rRev.begin(), rRev.end());
	list<Vertex> lRet = Skip(lRev);
	list<Vertex> rRet = Skip(rRev);
	reverse(rRet.begin(), rRet.end());

	return (make_pair(lRet, rRet));
}

// Function: Skip
// Used to skip the continuous positions having single vertices

list<Vertex> PathsOnDBG::Skip(list<Vertex> l)
{
	list<Vertex> out;

	for(list<Vertex>::iterator it = l.begin(); it != l.end(); it ++)
	{
		if((*it).Size() == 1)
		{
			continue;
		}

		out.push_back(*it);
	}

	return out;
}

// Function: CoverVertices
// Used to cover the vertices in core area

void PathsOnDBG::CoverVertices(list<Vertex>& flagMap, list<Vertex> l, Vertex v, list<Vertex> r)
{
	flagMap.push_back(v);

	for(list<Vertex>::reverse_iterator it = l.rbegin(); it != l.rend(); it ++)
	{
		if((*it).Size() > 1)
		{
			flagMap.push_back(*it);
		}
		else
		{
			break;
		}
	}

	for(list<Vertex>::iterator it = r.begin(); it != r.end(); it ++)
	{
		if((*it).Size() > 1)
		{
			flagMap.push_back(*it);
		}
		else
		{
			break;
		}
	}
}

// Function: Size
// To return the number of paths in the set

int PathsOnDBG::Size()
{
	return _tupleSet.size();
}

// Function: Re-load the operator []
// To return the paths given index

PathTuple PathsOnDBG::operator [] (int i)
{
	return _tupleSet[i];
}

// Destructor function

PathsOnDBG::~PathsOnDBG()
{
	vector<PathTuple>().swap(_tupleSet);
}

// Print
void PathsOnDBG::Print()
{
	
	cout << "Paths On DBG: \n";
	cout << "Paths On DBG Size: "<< _tupleSet.size() << "\n";
	for (int i = 0; i < _tupleSet.size(); i ++)
	{
		cout << i+1 << "\t";
		Vertex cv = _tupleSet[i].Center.Value();
		for (list<Locations>::iterator it = cv.begin(); it != cv.end(); it++)
		{
			Locations n = *it;
			cout << n.Key(6).substr(0,6) << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}
