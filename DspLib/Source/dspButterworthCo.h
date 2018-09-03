#pragma once

namespace Dsp
{

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

int butterworthCoLP(
   int     aN,
   double  aFs,
   double  aFc,
   int*    aBSize,
   int*    aASize,
   double  aBArray[],
   double  aAArray[]);

int butterworthCoLPSize(
   int     aN,
   int*    aBSize,
   int*    aASize);


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate bandpass butterwoth filter coefficients.
// H(z) = B(z)/A(z)
//
// N        Filter order 2,4,6..
// Fs       Sampling frequency
// Fc1      Cutoff frequency
// Fc2      Cutoff frequency
// BSize    Number of B coefficients
// ASize    Number of A coefficients
// BArray   B coefficients
// AArray   A coefficients

int butterworthCoBP(
   int     aN,
   double  aFs,
   double  aFc1,
   double  aFc2,
   int*    aBSize,
   int*    aASize,
   double  aBArray[],
   double  aAArray[]);

int butterworthCoBPSize(
   int     aN,
   int*    aBSize,
   int*    aASize);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

