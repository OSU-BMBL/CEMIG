#include "Pattern.h"

// Constructor function

Pattern::Pattern(SequenceSet sequences, Location loc, int l, int r, int k)
{
//	cout << "Pattern Start:" << "\n";
//	cout << "pos: " << loc.Position << "\n";
//	cout << "l: " << l << "\n";
//	cout << "r: " << r << "\n";
	
	Sequence = loc.Sequence;
	Begin = loc.Position - l + 1;
	End = loc.Position + k + r;
	Length = End - Begin + 1;
	Strand = loc.Strand;
	
//	cout << "Sequence: " << loc.Sequence + 1 << "\n";
//	cout << "Strand: " << loc.Strand << "\n";
//	cout << "Begin: " << loc.Position - l + 1 << "\n";
//	cout << "End: " << loc.Position + k + r << "\n";
//	cout << "Length: " << End - Begin + 1 << "\n";
	
	Str = PrintMotif(sequences, loc, l, r, k);
	
//	cout << "Pattern END" << "\n\n";
}

// Destructor Function

Pattern::~Pattern()
{
	string().swap(Str);
}

// Function: PrintMotif
// To print the motif pattern

string Pattern::PrintMotif(SequenceSet sequences, Location loc, int l, int r, int k)
{
//	cout << "PrintMotif Start:" << "\n";
	
	string s;

//	cout << "\n" << loc.Sequence+1 << "\t" << loc.Position-l << "\t" << l+r+k << "\t";
//	if(loc.Strand) cout << "+"; else cout << "-";
	
	if(loc.Strand)
	{
		s = sequences[loc.Sequence].String.substr(loc.Position - l , l + r + k);
//		cout << "string: " << s << "\n";
	}
	else
	{
		s = GetRev(sequences[loc.Sequence].String.substr(loc.Position - r , l + r + k));
//		cout << "string: " << s << "\n";
	}
	
//	cout << "PrintMotif END:" << "\n";

	return s;
}

// Function: GetRev
// To get the reverse string of current string

string Pattern::GetRev(string s)
{
	string r;

	for(int i = s.length() - 1; i >= 0; i --)
	{
		switch(s[i])
		{
			case 'A':
				r += 'T';
				break;
			case 'C':
				r += 'G';
				break;
			case 'G':
				r += 'C';
				break;
			case 'T':
				r += 'A';
				break;
			default:
				r += 'N';
				break;
		}
	}

	return r;
}
