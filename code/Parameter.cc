// Class: Parameters
// Used to build a parameter class to hold parameters

#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <getopt.h>

//#include <io.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "Parameter.h"

using namespace std;

/***************************************************************************/ 
/* ./cemig or ./cemig -h will pop up the usage of CEMIG */
static const char USAGE[] = 
"===================================================================\n\
[Usage]\n\
$ ./cemig --InputFile filename [argument list]\n\
===================================================================\n\
[Input]\n\
--InputFile(-I) : Input file with standard FASTA file format in default\n\n\
[Optional Input]\n\
--InputFileFormat(-F) : Input file format with FASTA in default\n\
--GenomeFile(-G) : Genome files with standard FASTA file format(required to generate FASTA file by BED format input)\n\
===================================================================\n\
[Output]\n\
Commonly used parameters\n\
--OutFileNamePrefix(-O) : Output file path and prefix(current dir in defaut)\n\
Advanced parameters\n\
--Debug(-D) : Print debug logs\n\
===================================================================\n\
[Motif]\n\
--Paired-end(-P) : Whether the input data is paired-end (true in defalut)\n\
===================================================================\n";

// Default constructor function

Parameter::Parameter()
{
	GenomeFastaFile = "Gemome/hg38.fa";
	InputFilePath = "data/test.fa";
	InputFileName = "test.fa";
	InputFileType = "fasta";
	OutFilePath = "out/motif";
	OutFileNamePrefix = "motif";
	MaxMotifs = 100; 
	NumberOfKmers = 100;
	Width = 6;
	Gap = 4;
	
	Pair = true;
	Debug = false;
}


/* arrange input parameters */
	
static struct option longOpts[] = 
{
    {"InputFile", required_argument, NULL, 'i'},
    {"InputFileFormat", required_argument, NULL, 'f'},
    {"GenomeFile", required_argument, NULL, 'g'},
    {"OutFileNamePrefix", required_argument, NULL, 'o'},
    {"Pair-end", no_argument, NULL, 'p'},
    {"Debug", no_argument, NULL, 'd'},
    {"Help", no_argument, NULL, 'h'},
    {"Width", required_argument, NULL, 'k'},
    {"Gap", required_argument, NULL, 0},
    {"Numberofkmers", required_argument, NULL, 'T'},
    {"MaxMotifs", required_argument, NULL, 'n'},
    {NULL, 0, NULL, 0},
};

Parameter::Parameter(int argc, char* argv[])
{
	//cout << "Get input parametes started";
	
	int op;
	int option_index = 0;
	bool is_valid = true;
	
	/* get default value of parameters */
	GenomeFastaFile = "Gemome/hg38.fa";
	InputFilePath = "data/test.fa";
	InputFileName = "test.fa";
	InputFileType = "FASTA";
	OutFilePath = "out/motif";
	OutFileNamePrefix = "motif";
	MaxMotifs = 100; 
	NumberOfKmers = 100;
	Width = 6;
	Gap = 4;
	Pair = false;
	Debug = false;
	
	/* get pwd */
	getcwd(PWD,sizeof(PWD));
	sprintf(PWD,"%s", PWD);
	while ((op = getopt_long(argc, argv, "i:f:g:o:k:T:n:pdh", longOpts, &option_index)) != -1)
	{
		//verboseDot();
		switch(op)
		{
			case 'i': 
				InputFilePath.assign(optarg);	
				InputFileName = InputFilePath.substr(InputFilePath.find_last_of("/")+1);
				OutFileNamePrefix = InputFilePath.substr(InputFilePath.find_last_of("/")+1, InputFilePath.find_last_of(".")-InputFilePath.find_last_of("/")-1);
				char outfile[255];	sprintf(outfile,"%s.out", &InputFilePath[0]);	
				OutFilePath = outfile;
				break;
			case 'f':
				InputFileType.assign(optarg);
				break;
			case 'g': 
				GenomeFastaFile.assign(optarg);
				break;
			case 'o':
				OutFilePath.assign(optarg);
				OutFileNamePrefix = OutFilePath.substr(OutFilePath.find_last_of("/")+1);
				OutFilePath = OutFilePath.substr(0,OutFilePath.find_last_of("/"));
				break;
			case 'k':
				Width = atoi(optarg);
				break;
			case 'T':
				NumberOfKmers = atoi(optarg);
				break;
			case 'n':
				MaxMotifs = atoi(optarg);
				break;
			case 'p':
				Pair = true;
				break;
			case 'd':
				Debug = true;
				DEBUG = true;
				break;
			case 'h':
				cout << USAGE << "\n";
				exit(1);
			default:
			cout << "\nUnrecognized parameters!!\n\n";
			cout << USAGE << "\n";
			exit(1);
		}
	}	
	
	uglyTime((char*)"\nSignal of parameters inputting complete");
	
	/* check input data existence */	
	char inputfile[255];
	sprintf(inputfile,"%s", &InputFilePath[0]);
	if(access(inputfile,00) != 0) 
	{
		cout << "Unable to find input file!!\n\n";
		exit(1);
	}
	
	/* check parameter completeness*/
	
	if(InputFileType != "FASTA" && InputFileType != "BED") 
	{
		cout << "Unsupported input format!!(Only FASTA or BED invalid)\n";
		exit(1);
	}	
	
	/* create output files */
	sprintf(OUTPUTFILE,"%s", &OutFilePath[0]);
	mkdir(OUTPUTFILE, S_IRWXU);
	
	chdir(OUTPUTFILE);

	if (DEBUG)
	{
		mkdir("Debug", S_IRWXU);
		ofstream fout;

		if(access("./Debug/Parameter",F_OK) == 0) remove("./Debug/Parameter");
		fout.open("./Debug/Parameter",ios::app);

		fout 	<< "Parameter: \n"
			<< "\n";
		for (int i = 0; i < argc; i++)
		{
			fout << argv[i] <<" ";		
		}
		fout 	<< "\n"
		 	<< "PWD: "<< PWD << endl
			<< "InputFilePath: "<< InputFilePath << endl
			<< "InputFileName: "<< InputFileName << endl
			<< "InputFileType: "<< InputFileType << endl
			<< "GenomeFastaFile: "<< GenomeFastaFile << endl
			<< "OutFilePath: "<< OutFilePath << endl
			<< "OutFileNamePrefix: "<< OutFileNamePrefix << endl
			<< "Width: "<< Width << endl
			<< "NumberOfKmers: "<< NumberOfKmers << endl
			<< "Gap: "<< Gap << endl
			<< "MaxMotifs: "<< MaxMotifs << endl
			<< "\n";

		fout.close();
	}

//	chdir(pwd);
	// printf("Parameter END!!\n");
}

// Destructor function

Parameter::~Parameter()
{}

void Parameter::Print(int argc, char** argv)
{
	cout 	<< "Parameter: \n"
		<< "\n";
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] <<" ";		
	}
	cout 	<< "\n"
	 	<< "PWD: "<< PWD << endl
		<< "InputFilePath: "<< InputFilePath << endl
		<< "InputFileName: "<< InputFileName << endl
		<< "InputFileType: "<< InputFileType << endl
		<< "GenomeFastaFile: "<< GenomeFastaFile << endl
		<< "OutFilePath: "<< OutFilePath << endl
		<< "OutFileNamePrefix: "<< OutFileNamePrefix << endl
		<< "Width: "<< Width << endl
		<< "NumberOfKmers: "<< NumberOfKmers << endl
		<< "Gap: "<< Gap << endl
		<< "MaxMotifs: "<< MaxMotifs << endl
		<< "\n";
}

