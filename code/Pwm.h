// Class: Pwm
// Used to define the motif profile

#ifndef _Pwm_H_
#define _Pwm_H_

using namespace std;

#include <vector>
#include <list>
#include "Pattern.h"
#include "MathBasis.h"

class Pwm
{
	private:
		vector<vector<double> > _mat;	// The matrix to hold the profile
		vector<vector<int> > _n;	// The matrix to hold the profile


	public:
		int Row, Col;	// The dimensons

		Pwm();	// Empty constructor function
		Pwm(int, int);	// Constructor function
		Pwm(list<Pattern>);	// Constructor function based on list of Patterns
		~Pwm();	// Destructor function
		double Value(int, int);	// Get rhe element in position (i, j)
		int Number(int, int);	// Get rhe element in position (i, j)
};

#endif
