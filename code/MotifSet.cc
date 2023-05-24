#include "MotifSet.h"

// Constructor function

MotifSet::MotifSet(PathsOnDBG paths, SequenceSet sequences, int k)
{
	cout << "\nGet motif seeds on paths started";
	fflush(stdout);
	
	ofstream fout;
	if (DEBUG)
	{
	    	if(access("./Debug/Motifseeds",F_OK) == 0) remove("./Debug/Motifseeds");
	    	fout.open("./Debug/Motifseeds",ios::app);
	}
	
	for(int i = 0; i < paths.Size(); i ++)
	{
		
	
		vector<Vertex> cleanL = List2Vector(paths[i].Left);
		Node vertex = paths[i].Center;
		vector<Vertex> cleanR = List2Vector(paths[i].Right);

		vector<Location> baseLocations = GetBase(vertex);
//		map<Location, bool> lFlag, rFlag;
		list<Location> lFlag, rFlag;
		
		for(vector<Location>::iterator it = baseLocations.begin(); it != baseLocations.end(); it ++)
		{
			lFlag.push_back(*it);
			rFlag.push_back(*it);
		}
		
		for(vector<Location>::iterator it = baseLocations.begin(); it != baseLocations.end(); it ++)
		{
			Location baseLocation = *it;
			
			bool locationFlag = true;
			int index = 0;

			for(vector<Vertex>::iterator it2 = cleanL.begin(); it2 != cleanL.end(); it2 ++)
			{
				bool positionFlag = false;
				Vertex v = *it2;
				index ++;

				for(Vertex::iterator it3 = v.begin(); it3 != v.end(); it3 ++)
				{
					Locations locations = *it3;
					
					for(Locations::iterator it4 = locations.begin(); it4 != locations.end(); it4 ++)
					{
						Location location = *it4;

						if(location.Sequence != baseLocation.Sequence)
						{
							continue;
						}

						if(location.Strand != baseLocation.Strand)
						{
							continue;
						}

						if(location.Position != baseLocation.Position - 
						  (baseLocation.Strand ? 1 : -1) * (1 + cleanL.size() - index))
						{
							continue;
						}

						positionFlag = true;

						break;
					}

					if(positionFlag == true)
					{
						break;
					}
				}

				if(positionFlag == false)
				{
					locationFlag = false;
					lFlag.remove(baseLocation);
					break;
				}
			}
		}
		
		for(vector<Location>::iterator it = baseLocations.begin(); it != baseLocations.end(); it ++)
		{
			Location baseLocation = *it;
			bool locationFlag = true;
			int index = cleanR.size();
			
			for(vector<Vertex>::reverse_iterator it2 = cleanR.rbegin(); it2 != cleanR.rend(); it2 ++)
			{
				bool positionFlag = false;
				Vertex v = *it2;
				index --;

				for(Vertex::iterator it3 = v.begin(); it3 != v.end(); it3 ++)
				{
					Locations locations = *it3;
					
					for(Locations::iterator it4 = locations.begin(); it4 != locations.end(); it4 ++)
					{
						Location location = *it4;

						if(location.Sequence != baseLocation.Sequence)
						{
							continue;
						}

						if(location.Strand != baseLocation.Strand)
						{
							continue;
						}

						if(location.Position != baseLocation.Position + 
						  (baseLocation.Strand ? 1 : -1) * (index + 1))
						{
							continue;
						}

						positionFlag = true;

						break;
					}

					if(positionFlag == true)
					{
						break;
					}
				}

				if(positionFlag == false)
				{
					locationFlag = false;
					rFlag.remove(baseLocation);

					break;
				}
			}
		}
		
		list<Location> lRet, rRet;

		for(list<Location>::iterator mapIt = lFlag.begin(); mapIt != lFlag.end(); mapIt ++)
		{
//			if(mapIt -> second == true)
//			{
				lRet.push_back(*mapIt);
//			}
		}
		
		for(list<Location>::iterator mapIt = rFlag.begin(); mapIt != rFlag.end(); mapIt ++)
		{
//			if(mapIt -> second == true)
//			{
				rRet.push_back(*mapIt);
//			}
		}
		
		MathBasis mb;
		list<Location> joinRet = mb.Intersect(lRet, rRet);	// Get the intersection

		double overlapRatio = (double) joinRet.size() / (double) baseLocations.size();
		if (cleanL.size() == 0 || cleanR.size() == 0) overlapRatio = 0;
		if (cleanL.size() == 0 && cleanR.size() == 0) overlapRatio = 1;
		
//		cout << "Path: " << i + 1 << "\n";
//		cout << "joinRet: " << joinRet.size() << "\n";
//		cout << "baseLocations: " << baseLocations.size() << "\n";
//		cout << "lRet: " << lRet.size() << "\n";
//		cout << "rRet: " << rRet.size() << "\n";
//		cout << "cleanL: " << cleanL.size() << "\n";
//		cout << "cleanR: " << cleanR.size() << "\n";
//		cout << "overlapRatio: " << overlapRatio << "\n\n";
		
	    	if (DEBUG) fout << "Motif seeds in path " << i+1 <<" with overlapRatio " << overlapRatio;
		if(overlapRatio >= C1)
		{
//			cout << "\ncase 1" << "\n";
			
			list<Location> outL = mb.Union(lRet, rRet);
			list<Pattern> patterns = Locations2Patterns(outL, sequences, cleanL.size(), cleanR.size(), k);	
			
//			cout << "patterns: " << patterns.size() << "\n";
			
			_motifs.push_back(Motif(patterns));
			if (DEBUG)
			{
	    			fout << " for case 1." << "\n\n";
	    			fout << "Motif seeds 1 " << "\n\n";
	    			for (int i = 0; i < Motif(patterns).Nsites; i ++)
	    			{
	    				Pattern pattern = (Motif(patterns))[i];
	    				fout << pattern.Str;
	    				fout << "\n";
	    			}
	    			fout << "\n";
			}
	    		fout << "\n";
		}
		else if(overlapRatio < C2)
		{
//			cout << "\ncase 2" << "\n";
			
			if (cleanL.size() > 0 && lRet.size() > 0)
			{
				list<Pattern> patternsL = Locations2Patterns(lRet, sequences, cleanL.size(), 0, k);
//				cout << "patternsL: " << patternsL.size() << "\n";
				_motifs.push_back(Motif(patternsL));	
			}
			
			
			if (cleanR.size() > 0 && rRet.size() > 0)
			{
				list<Pattern> patternsR = Locations2Patterns(rRet, sequences, 0, cleanR.size(), k);	
//				cout << "patternsR: " << patternsR.size() << "\n";	
				_motifs.push_back(Motif(patternsR));	
			}
			
			if (DEBUG)
			{
	    			fout << " for case 2." << "\n\n";
				if (cleanL.size() > 0 && lRet.size() > 0)
				{
	    				fout << "Motif seeds 1 " << "\n\n";
					list<Pattern> patternsL = Locations2Patterns(lRet, sequences, cleanL.size(), 0, k);
		    			for (int i = 0; i < Motif(patternsL).Nsites; i ++)
		    			{
		    				Pattern pattern = (Motif(patternsL))[i];
		    				fout << pattern.Str;
		    				fout << "\n";
		    			}
		    			fout << "\n";
	    			}
				if (cleanR.size() > 0 && rRet.size() > 0)
				{
		    			fout << "Motif seeds 2 " << "\n\n";
					list<Pattern> patternsR = Locations2Patterns(rRet, sequences, 0, cleanR.size(), k);	
		    			for (int i = 0; i < Motif(patternsR).Nsites; i ++)
		    			{
		    				Pattern pattern = (Motif(patternsR))[i];
		    				fout << pattern.Str;
		    				fout << "\n";
		    			}
		    			fout << "\n";
	    			}
			}
		}
		else
		{
//			cout << "\ncase 3" << "\n";
			
		//	_motifs.push_back(Motif(Locations2Patterns(joinRet, sequences, cleanL.size(), cleanR.size(), k)));
		//	_motifs.push_back(Motif(Locations2Patterns(lRet, sequences, cleanL.size(), 0, k)));
		//	_motifs.push_back(Motif(Locations2Patterns(rRet, sequences, 0, cleanR.size(), k)));
			list<Pattern> patternsL = Locations2Patterns(lRet, sequences, cleanL.size(), 0, k);
			
//			cout << "patternsL: " << patternsL.size() << "\n";
			
			list<Pattern> patternsR = Locations2Patterns(rRet, sequences, 0, cleanR.size(), k);
			
//			cout << "patternsR: " << patternsR.size() << "\n";
			
			list<Pattern> patterns = Locations2Patterns(joinRet, sequences, cleanL.size(), cleanR.size(), k);
			
//			cout << "patternsL: " << patterns.size() << "\n";
			
			_motifs.push_back(Motif(patternsL));
			_motifs.push_back(Motif(patternsR));
			_motifs.push_back(Motif(patterns));
			
			if (DEBUG)
			{
	    			fout << " for case 3." << "\n\n";
	    			fout << "Motif seeds 1 " << "\t" << Motif(patterns).Nsites << "\n\n";
	    			for (int i = 0; i < Motif(patterns).Nsites; i ++)
	    			{
	    				Pattern pattern = (Motif(patterns))[i];
	    				fout << pattern.Str;
	    				fout << "\n";
	    			}
	    			fout << "\n";
	    			fout << "Motif seeds 2 " << "\t" << Motif(patternsL).Nsites << "\n\n";
	    			for (int i = 0; i < Motif(patternsL).Nsites; i ++)
	    			{
	    				Pattern pattern = (Motif(patternsL))[i];
	    				fout << pattern.Str;
	    				fout << "\n";
	    			}
	    			fout << "\n";
	    			fout << "Motif seeds 3 " << "\t" << Motif(patternsR).Nsites << "\n\n";
	    			for (int i = 0; i < Motif(patternsR).Nsites; i ++)
	    			{
	    				Pattern pattern = (Motif(patternsR))[i];
	    				fout << pattern.Str;
	    				fout << "\n";
	    			}
	    			fout << "\n";
		 	}
		}
		if (i % 5 == 0) 
		{
			verboseDot();
		}	
	}
	
	fout.close();
	
	uglyTime((char*)"\nGet %d motif seeds", _motifs.size());
}

// Function: Locations2Patterns
// To transform Locations to Patterns

list<Pattern> MotifSet::Locations2Patterns(list<Location> loc, SequenceSet s, int l, int r, int k)
{
	
	list<Pattern> outP;

	for(list<Location>::iterator it = loc.begin(); it != loc.end(); it ++)
	{
		Pattern p(s, *it, l, r, k);
		outP.push_back(p);
	}
	return outP;
}

// Function: GetBase
// To get thecore part of the motif seed

vector<Location> MotifSet::GetBase(Node v)
{
	vector<Location> res;
	Vertex vertex = v.Value();
	int i = 0;

	for(Vertex::iterator it = vertex.begin(); it != vertex.end(); it ++)
	{
		for(Locations::iterator it2 = (*it).begin(); it2 != (*it).end(); it2 ++)
		{
			res.push_back(*it2);
		}
	}

	return res;
}

// Function: List2Vector
// To transform format

vector<Vertex> MotifSet::List2Vector(list<Vertex> l)
{
	vector<Vertex> v;
	v.reserve(l.size());

	for(list<Vertex>::iterator it = l.begin(); it != l.end(); it ++)
	{
		v.push_back(*it);
	}

	return v;
}

// Destructor function

MotifSet::~MotifSet()
{
	vector<Motif>().swap(_motifs);
}

int MotifSet::Size()
{
	return _motifs.size();
}

// Get the i-th sequence

Motif MotifSet::operator [](int i)
{
	return _motifs[i];
}


void MotifSet::Print()
{
	cout << "Motif Seeds Size: "<< _motifs.size() << endl;
	for (int i = 0; i < _motifs.size(); i ++)
	{
		cout << i+1 << "\n";
		Motif motif = _motifs[i];
		motif.Print();
		cout << "\n";
	}
	cout << "\n";
}
