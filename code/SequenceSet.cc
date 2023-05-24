// Class: SequenceSet
// Used to hold a sequence set

#include "SequenceSet.h"
#include <iostream>
#include <unistd.h>
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define TOP_NUM 1

//#include <iostream>

// Constructor function without parameters

SequenceSet::SequenceSet()
{
	//cout << "SequenceSet Start:" << "\n";
	Sequence s;
	vector<Sequence> ss(1, s);
	Vector2SequenceSet(ss);
}

// Function to read sequences from a file path

vector<Sequence> SequenceSet::GetSequences(string InputDataName)
{
	cout << "\nGet sequences from input files started";
	
	chdir(PWD);
	
	ifstream InOp(InputDataName.c_str());
	stringstream Buffer;
	Buffer << InOp.rdbuf();
	string TotalSeq(Buffer.str());

	istringstream SegOp(TotalSeq);
	string OneLn;
	vector<string> AllLn;

	while(getline(SegOp, OneLn, '\n'))
	{
		AllLn.push_back(OneLn);
	}

	vector<Sequence> OutSeqSet;
	
	int ii = 0;
	int c = 1;
	for(int i = 0; i < AllLn.size(); i ++)
	{
		string seq_info = "";
		if(AllLn[i][0] == '>')
		{	
			char info[255];
			sprintf(info,"Seq_%d", ii);
			seq_info = info;
			ii++;
			OutSeqSet.push_back(Sequence(AllLn[i], AllLn[i + 1], seq_info));
		}
		if ((i+1) >= c*AllLn.size()/10) 
		{
			verboseDot();
			c++;
		}
	}
	
	chdir(OUTPUTFILE);
	
	uglyTime((char*)"\nGet %d sequences", AllLn.size()/2);

	return OutSeqSet;
}

// Constructor function from file path

SequenceSet::SequenceSet(string InputDataName)
{
	_sequences = GetSequences(InputDataName);
}

// Function: Vector2SequenceSet
// To transform vector of sequences into SequenceSet

void SequenceSet::Vector2SequenceSet(vector<Sequence> SeqVec)
{
	_sequences = SeqVec;
}

// Constructor function
// From vector of sequences

SequenceSet::SequenceSet(vector<Sequence> SeqVec)
{
	Vector2SequenceSet(SeqVec);
}

// Destructor function

SequenceSet::~SequenceSet()
{
	vector<Sequence>().swap(_sequences);
}

// Get the number of sequences

size_t SequenceSet::Size()
{
	return _sequences.size();
}

// Get the i-th sequence

Sequence SequenceSet::operator [](int i)
{
	return _sequences[i];
}

// Print the sequence information

int SequenceSet::Count()
{
	int count = 0;

	for(int i = 0; i < Size(); i ++)
	{
		count += _sequences[i].Length();
	}
	
	return count;
}

void SequenceSet::Print()
{
	int PrintSize = MIN(Size(), TOP_NUM);

	for(int i = 0; i < PrintSize; i ++)
	{
		_sequences[i].Print();

		cout << "\n";
	}
}
