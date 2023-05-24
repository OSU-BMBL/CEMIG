#include "Motif.h"

// Default constructor function

Motif::Motif() {}

// Constructor function based on list of Patterns

Motif::Motif(list<Pattern> patterns)
{
	_list = patterns;
	Nsites = _list.size();
	Length = 0;
	for (list<Pattern>::iterator it = _list.begin(); it != _list.end(); it ++)
	{
		Pattern pattern = *it;
		if (pattern.Length > Length) Length = pattern.Length;
	}
	Pwm p(_list);
	Prf = p;
}

// Destructor function

Motif::~Motif()
{
	_list.clear();
	list<Pattern>().swap(_list);
}

// Get the i-th pattern

Pattern Motif::operator [](int i)
{
	int j = 0;
	for (list<Pattern>::iterator it = _list.begin(); it != _list.end(); it ++)
	{
		Pattern pattern = *it;
		if (j == i) return pattern;
		j++;
	}
	return *_list.begin();
}

void Motif::Print()
{
	for (list<Pattern>::iterator it = _list.begin(); it != _list.end(); it ++)
	{
		Pattern pattern = *it;
		cout << pattern.Str;
		cout << "\n";
	}
	cout << "\n";
}
