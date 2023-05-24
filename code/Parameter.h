// Class: Parameters
// Used to build a parameter class to hold parameters

#ifndef _Parameter_H_
#define _Parameter_H_

using namespace std;

#include <string>
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "Global.h"
#include "Struct.h"

class Parameter
{
	public:
		string InputFilePath;
		string InputFileName;
		string InputFileType;
		string GenomeFastaFile;
		string OutFilePath;
		string OutFileNamePrefix;
		
		int Width;
		int NumberOfKmers;
		int Gap;
		int MaxMotifs;
		
		bool Debug;
		bool Pair;
		bool Footprint;
		
		Parameter();	// Default constructor function
		Parameter(int, char**);	// Constructor function
		~Parameter();	// Destructor function
		void Print(int, char**);
};

#endif
