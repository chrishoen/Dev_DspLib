#pragma once

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Central difference algorithms of Pavel Holobordko.
// Calculate FIR filter coefficients: Holob first derivative.
// H(z) = B(z)/A(z)
//
// N        Filter order 1,2,3..
// H        Time increment.
//
// BArray   B coefficients -N .. N <==> 0 .. 2N+1 

void doCalcCoeffFirstDerivative_Holob(
   int aN,
   double aH,
   double* aC,
   double* aB);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Central difference algorithms of Pavel Holobordko.
// Calculate FIR filter coefficients: Savitzky-Golay first derivative.
// H(z) = B(z)/A(z)
//
// N        Filter Size 3,5,7,9
// H        Time increment.
//
// CArray   C coefficients 0 .. (N-1)/2
// BArray   B coefficients 0 .. N-1 

// Calculate the central difference filter coefficents.
// Polynomial degree 1 or 2.
void doCalcCoeffFirstDerivative_SavGol12(
   int aN,
   double aH,
   double* aC,
   double* aB);

// Calculate the central difference filter coefficents.
// Polynomial degree 3 or 4.
void doCalcCoeffFirstDerivative_SavGol34(
   int aN,
   double aH,
   double* aC,
   double* aB);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

