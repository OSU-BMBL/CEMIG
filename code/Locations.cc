#include "Locations.h"
#include "iostream"

// Empty constructor function

Locations::Locations()
{
	// cout << "Locations Start:" << endl;
	Integer = 0;
}

// Constructor function

Locations::Locations(int integer)
{
	Integer = integer;
}

// Destructor funciton

Locations::~Locations()
{
	list<Location>().swap(_list);
}

// Function: Key
// Used to get the string corresponding to the integer

string Locations::Key(int Width)
{
	AcgtExtensions a;
	return a.ToAcgtString(Integer, Width);
}

// Function: UpdateOcurrenceInRandomData
// Used to update the occurrence in random data

void Locations::UpdateOccurrenceInRandomData(double getOccurrenceInRandomData)
{
	OccurrenceInRandomData = getOccurrenceInRandomData;
}

// Function: UpdatePval
// Used to update the P-values of the k-mer

void Locations::UpdatePval()
{
	PoissonEvaluator PoissonEval(OccurrenceInRandomData);

	//Pvalue = 1 - PoissonEval.Cdf(OccurrenceInInputData);
	Pvalue = 1 - PoissonEval.Cdf(_list.size());

	//cout << "_list.size: "<< _list.size() << "\n";
	//cout << "Pvalue: "<< Pvalue << "\n";
	NegLogPval = Pvalue > 0 ? -log10(Pvalue) : _ultimateNumber;
}

// Function:begin
// To return the beginning pointer

//list<Location>::iterator Locations::begin()
//{
//	return _list.begin();
//}

// Function: end
// To return the ending position

//list<Location>::iterator Locations::end()
//{
//	return _list.end();
//}

// Operator ==

bool Locations::operator ==(const Locations l)
{
	if(Integer == l.Integer)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Function: Add
// To add one Location

void Locations::Add(Location l)
{
	_list.push_back(l);
}


// Function: Size
// To return the size of locations

int Locations::Size()
{
	return _list.size();
}
