#ifndef _BUTTERWORTHCO_H_
#define _BUTTERWORTHCO_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate low pass butterwoth filter coefficients.
// H(z) = B(z)/A(z)
//
// N        Filter order 2,4,6..
// Fs       Sampling frequency
// Fc       Cutoff frequency
//
// BSize    Number of B coefficients
// ASize    Number of A coefficients
// BArray   B coefficients
// AArray   A coefficients

int butterworthco(
   int     aN,
   double  aFs,
   double  aFc,
   int*    aBSize,
   int*    aASize,
   double  aBArray[], 
   double  aAArray[]);


#endif

