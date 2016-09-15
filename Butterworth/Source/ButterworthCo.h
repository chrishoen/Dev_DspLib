#ifndef _BUTTERWORTHCO_H_
#define _BUTTERWORTHCO_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate low pass butterwoth filter coefficients.
// H(z) = B(z)/A(z)
//
// N      Filter order
// Fs     Sampling frequency
// Fc     Cutoff frequency
// Nb     Number of B coefficients
// Na     Number of A coefficients
// B      B coefficients
// A      A coefficients

int butterworthco(
   int     aN,
   double  aFs,
   double  aFc,
   int*    aNb,
   int*    aNa,
   double* aB, 
   double* aA);


#endif

