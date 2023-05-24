// Struct: PathTuple
// Saved in tuple format

#ifndef _PathTuple_H_
#define _PathTuple_H_

using namespace std;

#include "Node.h"
#include "Vertex.h"

typedef struct
{
	list<Vertex> Left;
	Node Center;
	list<Vertex> Right;
} PathTuple;

#endif
