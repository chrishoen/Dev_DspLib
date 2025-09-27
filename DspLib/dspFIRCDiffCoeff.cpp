/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dsp_math.h"
#include "dsp_functions.h"

#include "dspFIRCDiffCoeff.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents.
// Polynomial degree 1 or 2.

void doCalcCoeff_Smoother_SavGol12(
   int aN,
   double* aC,
   double* aB)
{
   // Locals.
   int N = aN;
   int M = (N-1)/2;

   // Calculate coefficents.
   for (int k = 0; k <= M; k++)
   {
      double m1 = double(N);
      aC[k] = 1.0/m1;
   }

   for (int k = 0; k <= M; k++)
   {
      aB[M + k] = aC[k];
      aB[M - k] = aC[k];
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents.
// Polynomial degree 3 or 4.

void doCalcCoeff_Smoother_SavGol34(
   int aN,
   double* aC,
   double* aB)
{
   int N = aN;
   int M = (N-1)/2;

   // Calculate the coefficients.
   for (int k = 0; k <= M; k++)
   {
      double m1 = double(N);
      double m2 = double(N*N);
      double k2 = double(k*k);
      double tTerm1 = (3*m2-7-20*k2)/4.0;
      double tTerm2 = m1*(m2-4)/3.0;

      aC[k] = tTerm1/tTerm2;
   }

   for (int k = 0; k <= M; k++)
   {
      aB[M + k] = aC[k];
      aB[M - k] = aC[k];
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents.
// Polynomial degree 1 or 2.

void doCalcCoeff_FirstDerivative_SavGol12(
   int aN,
   double aH,
   double* aC,
   double* aB)
{
   // Locals.
   double tH = aH;

   int N = aN;
   int M = (N-1)/2;

   // Calculate the coefficients.
   for (int k = 0; k <= M; k++)
   {
      double m1 = double(N);
      double m2 = double(N*N);
      double k1 = double(k);

      double tTermH = 1/tH;
      double tTerm1 = k1;
      double tTerm2 = m1*(m2 - 1)/12;

      aC[k] = tTermH*tTerm1 / tTerm2;
   }

   aC[0] = 0;
   for (int k = 0; k <= M; k++)
   {
      aB[M + k] = -aC[k];
      aB[M - k] = aC[k];
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents.
// Polynomial degree 3 or 4.

void doCalcCoeff_FirstDerivative_SavGol34(
   int aN,
   double aH,
   double* aC,
   double* aB)
{
   // Locals.
   double tH = aH;

   int N = aN;
   int M = (N-1)/2;

   // Calculate the coefficients.
   for (int k = 0; k <= M; k++)
   {
      double m1 = double(N);
      double m2 = double(N*N);
      double m4 = double(N*N*N*N);
      double k1 = double(k);
      double k2 = double(k*k);
      double k3 = double(k*k*k);

      double tTermH = 1/tH;
      double tTerm1 = 5*(3*m4 - 18*m2 + 31)*k1 -28*(3*m2 - 7)*k3;
      double tTerm2 = m1*(m2 - 1)*(3*m4 - 39*m2 + 108)/15;

      aC[k] = tTermH*tTerm1/tTerm2;
   }

   aC[0] = 0;
   for (int k = 0; k <= M; k++)
   {
      aB[M + k] = -aC[k];
      aB[M - k] = aC[k];
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace