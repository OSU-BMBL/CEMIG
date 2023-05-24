// Class: PoissonEvaluator
// Used to build Poisson model for purpose of evaluating the P-value

#ifndef _PoissonEvaluator_H_
#define _PoissonEvaluator_H_

using namespace std;

#include <iostream>
#include <math.h>
#include "MathBasis.h"

class PoissonEvaluator
{
	private:
		double _lambda;	// The variable labmda used in calculating the Poisson function
		double LogFactorial(int);	// Calculate the logarithm of factorial

	public:
		PoissonEvaluator(double);	// Constructor function
		~PoissonEvaluator();	// Destructor function
		double Cdf(int);	// Calculate the cumulative function value
};

#endif
