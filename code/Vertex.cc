#include "Vertex.h"

// Empty constructor function

Vertex::Vertex() {}

// Constructor function

Vertex::Vertex(Locations id)
{
	list<Locations> lst(1, id);
	_locationsList = lst;
}

// Constructor function

Vertex::Vertex(list<Locations> lst)
{
	_locationsList = lst;
}

// Constructor function

Vertex::Vertex(vector<Locations> vec)
{	
	//cout << "vec.size:" << vec.size() << "\n";
	//for (int i = 0; i < vec.size();i++)
	//{
		//cout << "vec:" << vec[i].Size() << "\n";
	//}
	for(vector<Locations>::iterator it = vec.begin(); it != vec.end(); it ++)
	{
		//cout << "it:" << (*it).Size() << "\n";
		_locationsList.push_back(*it);
		//cout << "_locationsList:" << _locationsList.size() << "\n";
	}
	//cout << "Vertex END:" << "\n";
}

// Destructor function

Vertex::~Vertex()
{
	list<Locations>().swap(_locationsList);
}

// Function: Size
// Used to return the number of Locations in the vertex

int Vertex::Size()
{
	return _locationsList.size();
}

// Function: begin
// Used to return the beginning position of Vertex

//list<Locations>::iterator Vertex::begin()
//{
//	return _locationsList.begin();
//}

// Function: end
// Used to return the ending position of Vertex

//list<Locations>::iterator Vertex::end()
//{
//	return _locationsList.end();
//}

// Function: operator ==
// To check whether the two vertices are equal

bool Vertex::operator == (Vertex v2)
{
	if(_locationsList.size() != v2.Size())
	{
		return false;
	}

	bool res = true;

	for(Vertex::iterator it = _locationsList.begin(); it != _locationsList.end(); it ++)
	{
		bool flag = false;

		for(Vertex::iterator it2 = v2.begin(); it2 != v2.end(); it2 ++)
		{
			if((*it).Integer == (*it2).Integer)
			{
				flag = true;
				break;
			}
		}

		if(flag == false)
		{
			res = false;

			break;
		}
	}

	return res;
}
