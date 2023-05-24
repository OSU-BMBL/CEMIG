#include "Location.h"
// Constructor function

Location::Location(int sequence, int position, bool strand)
{
	Sequence = sequence;
	Position = position;
	Strand = strand;
	if (position == -1)
	{
	    cout << "\n position = -1 !!! \n";
	    cout << "\n" << Sequence+1 << "\t" << Position << "\n";
	    exit(0);
	}
}

// Desutructor function

Location::~Location() {}

// Operator ==

bool Location::operator == (const Location l)
{
	if(Sequence != l.Sequence)
	{
		return false;
	}
	
	if(Position != l.Position)
	{
		return false;
	}

	if(Strand != l.Strand)
	{
		return false;
	}

	return true;
}


