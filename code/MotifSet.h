// Class: MotifSet
// To hold the motif set

#ifndef _MotifSet_H_
#define _MotifSet_H_

using namespace std;

#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include "Motif.h"
#include "SequenceSet.h"
#include "PathsOnDBG.h"
#include "Location.h"
#include "MathBasis.h"
#include "Pattern.h"
#include "Node.h"
#include "Vertex.h"
#include "Struct.h"
#include "Global.h"

class MotifSet
{
	private:
		vector<Motif> _motifs;

	public:
		MotifSet(PathsOnDBG, SequenceSet, int);
		~MotifSet();
		list<Pattern> Locations2Patterns(list<Location>, SequenceSet, int, int, int);
		vector<Location> GetBase(Node);	// Get the core part of motif seed
		vector<Vertex> List2Vector(list<Vertex>);	// Transform format
		Motif operator [] (int);	// Get one motif
		int Size();
		void Print();
};

#endif
