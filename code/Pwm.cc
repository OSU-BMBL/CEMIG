#include "Pwm.h"

// Empty constructor function

Pwm::Pwm()
{
	Row = ALPHABET_SIZE;
	Col = LENGTH;
}

// Constructor function

Pwm::Pwm(int row, int col)
{
	Row = row;
	Col = col;
	vector<double> v(col);

	for(int i = 0; i < Row; i ++)
	{
		_mat.push_back(v);
	}
}

// Constructor function based on list of Patterns

Pwm::Pwm(list<Pattern> patterns)
{
	if(patterns.size() == 0)
	{
		cerr << "Error: Empty locations!\n";
		exit(0);
	}

	Row = ALPHABET_SIZE;
	Col = patterns.front().Length;
	vector<double> v(Col);
	vector<int> nv(Col);

	for(int i = 0; i < Row; i ++)
	{
		_mat.push_back(v);
		_n.push_back(nv);
	}

	for(list<Pattern>::iterator it = patterns.begin(); it != patterns.end(); it ++)
	{
		for(int i = 0; i < (*it).Length; i ++)
		{
			switch((*it).Str[i])
			{
				case 'A':
					_mat[0][i] ++;
					break;

				case 'C':
					_mat[1][i] ++;
					break;

				case 'G':
					_mat[2][i] ++;
					break;

				case 'T':
					_mat[3][i] ++;
					break;

				default:
					_mat[0][i] += 0.25;
					_mat[1][i] += 0.25;
					_mat[2][i] += 0.25;
					_mat[3][i] += 0.25;
					break;
			}
		}
	}

	for(int i = 0; i < Row; i ++)
	{
		for(int j = 0; j < Col; j ++)
		{
			_n[i][j] = _mat[i][j];
			_mat[i][j] /= patterns.size();
		}
	}
}

// Destructor function

Pwm::~Pwm()
{
	for(int i = 0; i < Row; i ++)
	{
		vector<double>().swap(_mat[i]);
	}

	vector<vector<double> >().swap(_mat);
}

// Function: Value
// Used to return the elements in specific position

double Pwm::Value(int i, int j)
{
	return _mat[i][j];
}

int Pwm::Number(int i, int j)
{
	return _n[i][j];
}
