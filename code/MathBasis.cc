#include "MathBasis.h"
#include "stdlib.h"
#include <iostream>

// Function: partition
// Used to divide the sort task into smaller ones

// Constructor function

MathBasis::MathBasis()
{
	_a = 0;
}

// Destructor function

MathBasis::~MathBasis() {}

//template <class T>
int MathBasis::partition(double a[], int start, int stop, int id[])
{
	int tmpid, up = start, down = stop - 1;
	double tmpvalue, part = a[stop];

	if (stop <= start ) return start;

	int i = 0;

	while (true)
	{
		//cout << i+1 << "	";
		//cout << "up:" << up << "	";
		//cout << "down:" << down << "\n";
		while (a[up] < part) 
		{
			up ++;
			//cout << "up:" << up << "\n";
		}
		while (part < a[down] && up < down) 
		{
			down --;
			//cout << "down:" << down << "\n";
		}

		if (up >= down) break;
		
		//cout << "a[up]:" << a[up] << "	";
		//cout << "a[down]:" << a[down] << "	";
		//cout << "id[up]:" << id[up] << "	";
		//cout << "id[down]:" << id[down] << "\n";

		tmpvalue = a[up]; a[up] = a[down]; a[down] = tmpvalue;
		tmpid = id[up]; id[up] = id[down]; id[down] = tmpid;

		//cout << "a[up]:" << a[up] << "	";
		//cout << "a[down]:" << a[down] << "	";
		//cout << "id[up]:" << id[up] << "	";
		//cout << "id[down]:" << id[down] << "\n";

		up ++; down --;i++;
	}
	//cout << i+1 << "	";
	//cout << "up:" << up << "	";
	//cout << "down:" << down << "\n";

	tmpvalue = a[up]; a[up] = a[stop]; a[stop] = tmpvalue;
	tmpid = id[up]; id[up] = id[stop]; id[stop] = tmpid;

	return up;
}

// Function: quickSort
// Used to sort the elements in an array in creasing order

//template <class T>
void MathBasis::quickSort(double a[], int start, int stop, int id[])
{
	int i;

	if (stop <= start) 
	{
		return;
	}

	i = partition(a, start, stop, id);
	//cout << "i:" << i << "\n";
	quickSort(a, start, i - 1, id);
	quickSort(a, i + 1, stop, id);
}

// Function: Intersect
// To get the intersection between two lists

//template <class T>
//list<T> MathBasis<T>::Intersect(list<T> l1, list<T> l2)
//{
////	map<T, bool> tmpMap;
//	list<T> outL = l1;
//	list<T> tmpMap = l1;
//
////	for(typename list<T>::iterator it = l1.begin(); it != l1.end(); it ++)
////	{
////		tmpMap[*it] = true;
////	}
//
//	for(typename list<T>::iterator it = l2.begin(); it != l2.end(); it ++)
//	{
//		if(find(tmpMap.begin(), tmpMap.end(), *it) == tmpMap.end())
//		{
//			outL.remove(*it);
//		}
//
////		if(tmpMap.count(*it) > 0)
////		{
////			outL.push_back(*it);
////		}
//	}
//
//	return outL;
//}

//template <class T>
list<Location> MathBasis::Intersect(list<Location> l1, list<Location> l2)
{
//	map<T, bool> tmpMap;
	list<Location> outL = l1;
	list<Location> tmpMap = l1;

//	for(typename list<T>::iterator it = l1.begin(); it != l1.end(); it ++)
//	{
//		tmpMap[*it] = true;
//	}

	for(list<Location>::iterator it = l2.begin(); it != l2.end(); it ++)
	{
		if(find(tmpMap.begin(), tmpMap.end(), *it) == tmpMap.end())
		{
			outL.remove(*it);
		}

//		if(tmpMap.count(*it) > 0)
//		{
//			outL.push_back(*it);
//		}
	}

	return outL;
}

// Function: Union
// To et the union of two lists

//template <class T>
list<Location> MathBasis::Union(list<Location> l1, list<Location> l2)
{
	list<Location> outL = l1;
//	map<T, bool> tmpMap;

//	for(typename list<T>::iterator it = l1.begin(); it != l1.end(); it ++)
//	{
//		tmpMap[*it] = true;
//	}

	for(list<Location>::iterator it = l2.begin(); it != l2.end(); it ++)
	{
		if(find(outL.begin(), outL.end(), *it) == outL.end())
		{
			outL.push_back(*it);
		}
	}

//	list<T> outL;

//	for(typename map<T, bool>::iterator it = tmpMap.begin(); it != tmpMap.end(); it ++)
//	{
//		outL.push_back(it -> first);
//	}

	return outL;
}
