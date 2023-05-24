#include <iostream>
#include <iomanip>
#include <cstring>
#include "Write_file.h"

#define PRECISE 4
char alphabet[4] = {'A', 'C', 'G', 'T'};

void print_params(FILE *fw1, Parameter parameter, SequenceSet sequences, MarkovModelMatrix markov)
{
	//
	fprintf(fw1, "#########################################\n#                                       #\n");
	fprintf(fw1, "#\tCEMIG version %s output\t#\n", VERSION.c_str());
	fprintf(fw1, "#                                       #\n#########################################\n");
	fprintf(fw1, "\n****************************************\n");
	fprintf(fw1, "INPUT DATA SUMMARY\n");
	fprintf(fw1, "****************************************\n");
	fprintf(fw1,"\nDatafile: %s\n",parameter.OutFileNamePrefix.c_str());
	fprintf(fw1,"Alphabet: A G C T\n");
	fprintf(fw1,"Nucleotides composition:\tA: %.2f   G: %.2f   C: %.2f   T: %.2f\n",markov.MatrixF(0),markov.MatrixF(1),markov.MatrixF(2),markov.MatrixF(3));
	fprintf(fw1,"Sequences number: %ld\nNucleotides number: %d\n",sequences.Size(),sequences.Count());
	//
	int i =0;
	fprintf(fw1,"\nSequence name\t\tLength\n");
	for (i = 0;i < sequences.Size(); i++)
	{
		fprintf (fw1,"%s\t\t%d\n", sequences[i].Info.c_str(), sequences[i].Length());
	}

	fprintf(fw1, "\n****************************************\n");
	fprintf(fw1, "COMMAND LINE SUMMARY\n");
	fprintf(fw1, "****************************************\n");
	fprintf(fw1, "\nParameters: -w %d; -n %d; -g %d; -m %d;", parameter.Width, parameter.NumberOfKmers, parameter.Gap, parameter.MaxMotifs);
	if (parameter.Pair) fprintf(fw1, " -p");
	fprintf(fw1, "\n\nLength of k-mer (-w)\t%d\nNumber of the k-mers taken as high significant (-n)\t%d\nThe gap allowed in motif (-g)\t%d\nThe max number of output motifs (-m)\t%d\nSeqences run type is paried_end  (-p)\tOn\n", 
	parameter.Width, parameter.NumberOfKmers, parameter.Gap, parameter.MaxMotifs);
	
	fprintf(fw1, "\n");
}

void print_closure(Parameter parameter, MotifSet motifs, SequenceSet sequences, MarkovModelMatrix markov)
{
	string fn1 = parameter.OutFileNamePrefix;
	fn1+=".closure";
	FILE *fw1 = mustOpen(fn1.c_str(), (char*)"w");
	print_params(fw1, parameter, sequences, markov);
	//
	int closure_output = 0, ii = 0, jj = 0, kk = 0;
	char **clo_TF;
	char **sequences_closures;
	while (ii < motifs.Size() && closure_output < parameter.MaxMotifs)
	{
		closure_output++;
		fprintf (fw1,"\n\n*********************************************************\n");
		fprintf (fw1," Candidate Motif %3d\n",closure_output);
		fprintf (fw1,"*********************************************************\n\n");
		fprintf (fw1," Motif length: %d\n Motif number: %d\n Seed number: %d\n Motif Pvalue: %d (%d)\n\n",motifs[ii].Length, -1, motifs[ii].Nsites, -1, -1);
		fprintf (fw1,"\n------------------- Motif Seed------------------\n");
		for (jj=0; jj<motifs[ii].Nsites; jj++) 
		{
			Pattern pattern = motifs[ii][jj];
			fprintf (fw1, "%s", pattern.Str.c_str());
			fprintf (fw1,"\n");
		}	
		fprintf (fw1,"\n------------------- Position weight matrix------------------\n");
		for (kk=0;kk<motifs[ii].Length;kk++)
			fprintf(fw1,"\t%d",kk+1);
		fprintf (fw1,"\n");
		for (jj=1;jj<5;jj++)
		{
			if (jj==1) fprintf (fw1, "A\t");
			if (jj==2) fprintf (fw1, "G\t");
			if (jj==3) fprintf (fw1, "C\t");
			if (jj==4) fprintf (fw1, "T\t");
			for (kk=0;kk<motifs[ii].Length;kk++)
			{
				fprintf (fw1, "%d\t",motifs[ii].Prf.Number(jj-1,kk));
			}
			fprintf (fw1, "\n");
		}
	}
}
void print_meme(Parameter parameter, MotifSet motifs, SequenceSet sequences, MarkovModelMatrix markov)
{
	string fn1 = parameter.OutFileNamePrefix;
	fn1+=".meme";
	FILE *fw1 = mustOpen(fn1.c_str(), (char*)"w");
	
	ofstream f_out_op(fn1.c_str());
	
	f_out_op<<"MEME version 4\n"<<endl;
	f_out_op<<"ALPHABET= ACGT\n"<<endl;

	if(parameter.Pair)
	{
		f_out_op<<"Strands: + -\n"<<endl;
	}
	else
	{
		f_out_op<<"Strands: +\n"<<endl;
	}

	f_out_op<<"Background letter frequencies (from dataset):\n";
	f_out_op.setf(ios::fixed);
	
	for(int i=0; i<3; i++)
	{
		f_out_op<<alphabet[i]<<" "<<fixed<<setprecision(PRECISE)<<markov.MatrixF(i)<<" ";
	}
	f_out_op<<alphabet[3]<<" "<<fixed<<setprecision(PRECISE)<<markov.MatrixF(3)<<endl<<endl;
	
	int num_mtf = parameter.MaxMotifs;
	if(parameter.MaxMotifs > motifs.Size())
	{
		num_mtf = motifs.Size();
	}


	for(int i = 0; i < num_mtf; i++)
	{
		f_out_op<<"MOTIF MOTIF-"<<i<<" MOTIF-" <<i<<endl;
		f_out_op<<"letter-probability matrix: alength= 4 w= "<<motifs[i].Length
			<<" nsites= "<<motifs[i].Nsites
			<<" score= "<< -1 <<endl;

		for(int j=0; j<motifs[i].Length; j++)
		{
			f_out_op.setf(ios::fixed);
			for(int k=0; k<3; k++)
			{
				f_out_op<<fixed<<setprecision(PRECISE)<<motifs[i].Prf.Value(k,j)<<" ";
			}
			f_out_op<<fixed<<setprecision(PRECISE)<<motifs[i].Prf.Value(3,j)<<endl;
		}

		f_out_op<<endl<<endl;
	}

	f_out_op<<endl;
	f_out_op.unsetf(ios::fixed);
	f_out_op<<"Time "<<clock1000()/1000.<<" secs.\n";
	f_out_op.close();
	
	//uglyTime((char*)"Program END");
	cout <<"\nThere're altogether " << num_mtf << " motifs output of all " << motifs.Size() << " motifs.\n";
	cout <<"Finished generating the motif file "<< fn1 <<" [Time " << clock1000()/1000. <<" secs]\n";
}
void print_binding_sites(Parameter parameter, MotifSet motifs, SequenceSet sequences, MarkovModelMatrix markov)
{
	string fn1 = parameter.OutFileNamePrefix;
	fn1+="_binding_sites.txt";
	FILE *fw1 = mustOpen(fn1.c_str(), (char*)"w");
	
	ofstream f_out_op(fn1.c_str());
	
	f_out_op<<"Binding Sites Generated by CEMIG\n"<<endl;
	
	int num_mtf = parameter.MaxMotifs;
	if(parameter.MaxMotifs > motifs.Size())
	{
		num_mtf = motifs.Size();
	}
	
	f_out_op<<"MOTIF_ID\tSequence\tBegin\tEnd\tSrand"<<endl;
	
	for(int i = 0; i < num_mtf; i++)
	{
		for(int j=0; j<motifs[i].Length; j++)
		{
		    f_out_op<<"MOTIF-"<<i<<"\t"<<motifs[i][j].Sequence<<"\t"<<motifs[i][j].Begin<<"\t"<<motifs[i][j].End<<"\t";
		    if(motifs[i][j].Strand)
        	{
        		f_out_op<<"+"<<endl;
        	}
        	else
        	{
        		f_out_op<<"-"<<endl;
        	}
		}
	}
	
	f_out_op.close();
	
}

