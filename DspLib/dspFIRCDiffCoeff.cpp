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
// Calculate coefficients.

void doCalcCoeffFirstDerivative_Holob(
   int aN,
   double aH,
   double* aC,
   double* aB)
{
   // Locals.
   double tH = aH;
   switch (aN)
   {
      case 3:
      {
         double tD = 2*aH;
         aC[0] = 0;
         aC[1] = 1/tD;
      }
      break;
      case 5:
      {
         double tD = 12*aH;
         aC[0] = 0;
         aC[1] = 8/tD;
         aC[2] = -1/tD;
      }
      break;
      case 7:
      {
         double tD = 60*aH;
         aC[0] = 0;
         aC[1] = 45/tD;
         aC[2] = -9/tD;
         aC[3] = 1/tD;
      }
      break;
      case 9:
      {
         double tD = 840*aH;
         aC[0] = 0;
         aC[1] = 672/tD;
         aC[2] = -168/tD;
         aC[3] = 32/tD;
         aC[4] = -3/tD;
      }
      break;
      default:
      {
         printf("doCalcCoeffFirstDerivative_Holob FAIL\n");
      }
   }

   int N = aN;
   int M = (N-1)/2;

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
// Polynomial degree 1 or 2.

void doCalcCoeffFirstDerivative_SavGol12(
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

void doCalcCoeffFirstDerivative_SavGol34(
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