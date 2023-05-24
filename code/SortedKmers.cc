#include "SortedKmers.h"
#include "stdlib.h"

// Empty constructor function

SortedKmers::SortedKmers()
{
	_t = 100;
	K = 6;
}

// Constructor function

//SortedKmers::SortedKmers(AllPossibleKmers a)
//{
//	_t = 100;
//	_list = a.SortP();
//}

// Constructor function

SortedKmers::SortedKmers(AllPossibleKmers AllPossibleK, int t)
{
	_t = t;
	K = AllPossibleK.K;

//	cout << "K:" << K << "\n";

	_list = AllPossibleK.SortP();
}

// Destructor function

SortedKmers::~SortedKmers()
{
	list<Locations>().swap(_list);
}

// Function: GetK1

list<Locations> SortedKmers::GetK1()
{
	//cout << "SortedKmers::GetK1:Start.\n";
	int i = 0;
	int j = _list.size();
	list<Locations>::iterator it = _list.begin();
	list<Locations> OutList;
	//cout << " _list.size():" << _list.size() << "\n";

	while(i < min(_t,j))
	{	
		//cout << " i:" << i << "\n";
		//cout << " _t:" << i << "\n";
		
		//if (i == 98)
		//{	cout << " i:" << i << "\n";
		//	cout << " _t:" << i << "\n";}
		OutList.push_back(*it);
		it ++;
		i ++;
	}

	//cout << "SortedKmers::GetK1:END.\n";
	return OutList;
}

// Function: GetK2

list<Locations> SortedKmers::GetK2()
{
	//cout << "SortedKmers:GetK2 Start:" << "\n";
	int i = 0;
	list<Locations>::iterator it = _list.begin();
	list<Locations> OutList;
	//cout << "_list:" << _list.size() << "\n";

	while(i < _list.size() / 2)
	{
		OutList.push_back(*it);
		it ++;
		i ++;
	}
	//cout << "SortedKmers:GetK2 END:" << "\n";

	return OutList;
}

// Function: GetK3

list<Locations> SortedKmers::GetK3()
{
	//cout << "SortedKmers::GetK3:Start.\n";
	int i = 0;
	int Mid = ceil(_list.size() / 2);
	list<Locations>::iterator it = _list.begin();
	list<Locations> OutList;

	while(it != _list.end())
	{
		if(i >= Mid)
		{
			OutList.push_back(*it);
		}

		i ++;
		it ++;
	}
	//cout << "SortedKmers::GetK3:END.\n";

	return OutList;
}

// 
// Function: Size
// Used to return the size of list

int SortedKmers::Size()
{
	return _list.size();
}

list<Locations> SortedKmers::List()
{
	return _list;
}
