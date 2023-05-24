// Class: Sequence
// Used to hold one sequence

#include "Sequence.h"
//#include <iostream>

// Default constructor function

Sequence::Sequence()
{
	Chrom = "chr10_ 22610878_22611813_._1000_._471.725544438908_-1_3.21510858105313_389";
	ChromStart = 22610878;
	ChromEnd = 22611813;
	Name = ".";
	Peak = 389;
	Pvalue = -1; 
	Qvalue = 3.21510858105313;
	Score = 1000;
	SignalValue = 471.725544438908; 
	Strand = '.';
	String = "";
}

// Constructor function

Sequence::Sequence(string Header, string Seq, string info)
{
	//cout << "Sequence Start:" << "\n";
    int pos;
	bool FlagA = false;
	pos = Header.find(":");
	while(pos != -1)
	{
		FlagA = true;
		Header.replace(pos,string(":").length(),"_");
		pos = Header.find(":");
	}
	
	if (FlagA)
	{
		pos = Header.find("-");
		while(pos != -1)
		{
			Header.replace(pos,string("-").length(),"_");
			pos = Header.find("-");
		}
	}
	
	for( int i = 0; i < Seq.size(); i++ )
	{
		Seq[i] = toupper(Seq[i]);
	}
	
	String = Seq;
	istringstream WordHd(Header);
	vector<string> WordVec;
	WordVec.reserve(10);
	string TmpWord;
	Info = info;

	while(getline(WordHd, TmpWord, '_'))
	{
		WordVec.push_back(TmpWord);
	}

	if(WordVec.size() < 3)
	{
//		Chrom = "chr10_22610878_22611813_._1000_._471.725544438908_-1_3.21510858105313_389";
		Chrom = "chr10";
		ChromStart = 22610878;
		ChromEnd = 22611813;
		Name = ".";
		Peak = 389;
		Pvalue = -1; 
		Qvalue = 3.21510858105313;
		Score = 1000;
		SignalValue = 471.725544438908; 
		Strand = '.';
	}
	if(WordVec.size() == 3)
	{
		Chrom = WordVec[0].substr(1);
		ChromStart = atoi(WordVec[1].c_str());
		ChromEnd = atoi(WordVec[2].c_str());
		Name = ".";
		Score = -1;
		Strand = '.';
		SignalValue = -1;
		Pvalue = -1;
		Qvalue = -1;
		Peak = -1;
	}
	if(WordVec.size() > 3)
	{
		Name = WordVec[3];
	}
	if(WordVec.size() > 4)
	{
		Score = atoi(WordVec[4].c_str());
	}
	if(WordVec.size() > 5)
	{
		Strand = WordVec[5][0];
	}
	if(WordVec.size() > 6)
	{
		SignalValue = atof(WordVec[6].c_str());
	}
	if(WordVec.size() > 7)
	{
		Pvalue = atof(WordVec[7].c_str());
	}
	if(WordVec.size() > 8)
	{
		Qvalue = atof(WordVec[8].c_str());
	}
	if(WordVec.size() > 9)
	{
		Peak = atoi(WordVec[9].c_str());
	}
}

// Destructor function

Sequence::~Sequence()
{
	string().swap(Name);
	string().swap(String);
}

// Get the length of the sequence

int Sequence::Length()
{
	return String.length();
}

// Index one element

int Sequence::operator [](int i)
{
	AcgtExtensions a;
	return a.ToByte(String[i]);
}

// Print the basic information of the sequence

void Sequence::Print()
{
	cout << "Chromosome: " << Chrom << "\n" 
		<< "Start: " << ChromStart << "\n" 
		<< "End: " << ChromEnd << "\n" 
		<< "Name: " << Name << "\n" 
		<< "Score: " << Score << "\n" 
		<< "Strand: " << Strand << "\n" 
		<< "Signal Value: " << SignalValue << "\n" 
		<< "Negative Logarithm P-value: " << Pvalue << "\n" 
		<< "Negative Logarithm q-value: " << Qvalue << "\n" 
		<< "Peak: " << Peak << "\n" 
		<< "Sequence: " << String.substr(0, 10) << " ...\n";
}

string replaceAWithX(string str, string str1, string str2)
{
	int pos;
	pos = str.find(str1);
	while(pos != -1)
	{
		str.replace(pos,string(str1).length(), str2);
		pos = str.find(str1);
    	}
	return str;
}
