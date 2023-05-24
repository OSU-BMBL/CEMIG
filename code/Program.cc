#include "Program.h"

#include <iomanip>
#include <iostream>

using namespace std;

// colors for the term's menu 
#define RESET "\033[m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RED "\033[1;31m"

// define our program name
#define PROGRAM_NAME "CEMIG"
#define VER "v0.01"

int cemig_help(void);
int cemig_faq(void);

// Main function

int main(int argc, char* argv[])
{	
	cout << setiosflags(ios::left);
 	
	/* Start the timer */
	uglyTime(NULL);
	
	if (argc < 2) return cemig_help();
	cout << "\nCEMIG " << VERSION << ": motif finding on genome scale (compiled " __DATE__ " " __TIME__ ")\n\n";

	Parameter InputParam(argc, argv);	// Input parameters

	bool Debug_ = InputParam.Debug;

	SequenceSet InputSeq(InputParam.InputFilePath);	// Read into input data (To be transformed into const variable?)

	GraphBuilder GBuilder(InputSeq);	// Generate the graph builder composed of De Beuijn Graph 
						// , Hamming Distance Graph, sorted k-mers, all possible k-mers and Markov model matrix
//	GBuilder.Print();	// Print the graphs

	HammingGraphCluster HGCluster(GBuilder.HDGraph);	// Get clusters from Hamming Distance Graph

	PathsOnDBG paths(GBuilder.DBGraph, HGCluster);	// Get paths on De Bruijn Grapjh

	MotifSet seeds(paths, InputSeq, InputParam.Width);	// Construct the seeds based on the paths

//	print_closure(InputParam, seeds, InputSeq, GBuilder.MarkovModelM);
	print_meme(InputParam, seeds, InputSeq, GBuilder.MarkovModelM);
	print_binding_sites(InputParam, seeds, InputSeq, GBuilder.MarkovModelM);

	return 0;
}

int cemig_help(void)
{
    cout  << "\n" << PROGRAM_NAME  << " is a powerful toolset for genome motif finding." << endl << endl;
    cout << "Version:   " << VERSION << "\n\n";
    return 0;
}


int cemig_faq(void)
{
    cout << "\n";

    cout << "Q1. How do I see the help for a given command?" << endl;
    cout << "A1. CEMIG commands have a \"-h\" option. Additionally, some tools " << endl;
    cout << "    will provide the help menu if you just type the command line " << endl;
    cout << "    followed by enter. " << endl;

    cout << "\n";
    return 0;
}


