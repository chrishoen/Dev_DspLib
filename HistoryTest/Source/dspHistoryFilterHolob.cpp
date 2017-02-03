/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dsp_math.h"
#include "dsp_functions.h"
#include "dspStatistics.h"
#include "dspHistoryFilterHolob.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryFilterHolob::HistoryFilterHolob(HistoryFilterParms& aParms)
{
   BaseClass::initialize(aParms);
   mBackAddFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryFilterHolob::show()
{
   BaseClass::show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply the linear operator from the input to the output. F:X->Y

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents, based on the parms.
// This coefficients are used to calculate the first derivative.

void HistoryFilterHolob::calculateCoefficientsSmoother()
{
   // Add the backward time terms.
   mBackAddFlag = true;

   // Locals.
   double tH = mParms.mH;

   int N = mParms.mFilterOrder;
   int m = (N-1)/2;

   double tTerm1 = 1.0/pow(2.0,double(2*m));

   // Calculate the coefficients.
   for (int k = 0; k <= m; k++)
   {
      int kp2 = k*k;
      long long tTerm2 = (3*m - 1 - 2*kp2);
      long long tTerm3 = dsp_binomial(2*m,m+k);
      long long tTerm4 = (2*m - 1);
      long long tTerm5 = (tTerm2*tTerm3)/tTerm4;

      mC[k] = tTerm1*double(tTerm5);
   }

   // Show.
   for (int k = 0; k <= m; k++)
   {
      printf("C[%3d]  %10.6f\n",k,mC[k]);
   }
   printf("\n");

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents, based on the parms.
// This coefficients are used to calculate the first derivative.

void HistoryFilterHolob::calculateCoefficientsFirstDerivative()
{
   // Subtract the backward time terms.
   mBackAddFlag = false;

   // Locals.
   double tH = mParms.mH;

   int N = mParms.mFilterOrder;
   int M = (N-1)/2;
   int m = (N-3)/2;

   double tTerm1 = 1.0/pow(2.0,double(2*m+1));
   double tTerm2 = 1.0/tH;

   // Calculate the coefficients.
   mC[0] = 0.0;

   for (int k = 1; k <= M; k++)
   {
      mC[k] = tTerm1*tTerm2*(double(dsp_binomial(2*m,m-k+1) - dsp_binomial(2*m,m-k-1)));
   }

   // Show.
   for (int k = 1; k <= M; k++)
   {
      printf("C[%3d]  %10.6f\n",k,mC[k]);
   }
   printf("\n");

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents, based on the parms.
// This coefficients are used to calculate the second derivative.

static long long recursive_s(int N, int M, int k)
{
   if(k >  M) return 0;
   if(k == M) return 1;
   return ((2*N-10)*recursive_s(N,M,k+1) - (N+2*k+3)*recursive_s(N,M,k+2))/(N-2*k-1);
}

void HistoryFilterHolob::calculateCoefficientsSecondDerivative()
{
   // Add the backward time terms.
   mBackAddFlag = true;
   mC[0] = 0.0;

   // Locals.
   double tH = mParms.mH;

   int N = mParms.mFilterOrder;
   int M = (N-1)/2;

   double tTerm1 = 1.0/pow(2.0,double(N-3));
   double tTerm2 = 1.0/(tH*tH);

   // Calculate the coefficients.
   for (int k = 0; k <= M; k++)
   {
      mC[k] = tTerm1*tTerm2*double(recursive_s(N,M,k));
   }

   // Show.
   for (int k = 0; k <= M; k++)
   {
      printf("C[%3d]  %10.6f\n",k,mC[k]);
   }
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply the linear operator from the input to the output. F:X->Y.
// This applies the central difference filter using the coefficients 
// calculated below.

void HistoryFilterHolob::operate(History& aX, History& aY)
{
   //***************************************************************************
   // Calculate the central difference filter coefficents, based on the parms.
   switch (mParms.mFilterType)
   {
   case HistoryFilterParms::cFilterSmoother:
   {
      calculateCoefficientsSmoother();
   }
   break;
   case HistoryFilterParms::cFilterFirstDeriv:
   {
      calculateCoefficientsFirstDerivative();
   }
   break;
   case HistoryFilterParms::cFilterSecondDeriv:
   {
      calculateCoefficientsSecondDerivative();
   }
   break;
   }

   //***************************************************************************
   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.
   BaseClass::createTimeClone(aX,aY);

   //***************************************************************************
   // Execute a loop to calculate the central difference sum to implement
   // the algorithm.

   // Locals
   int tP = aX.mNumSamples;
   int tN = mParms.mFilterOrder;
   int tM = (tN-1)/2;

   // For all of the samples in the source and destination arrays.
   for (int i = 0; i < tP; i++)
   {
      // For all of the coefficients (backward and forward are the same).
      double tSum = mC[0]*aX.mValue[i];
      for (int k = 1; k <= tM; k++)
      {
         // Calculate the forward  array index, trim at the end.
         int iF = dsp_imin(i + k,tP-1);
         // Calculate the backward array index, trim at the beginning.
         int iB = dsp_imax(i - k,0);
         // Accumulate the sum from forward  source samples and coefficients.
         tSum += mC[k]*aX.mValue[iF];
         // Accumulate the sum from backward source samples and coefficients.
         if (mBackAddFlag)
         {
            tSum += mC[k] * aX.mValue[iB];
         }
         else
         {
            tSum -= mC[k] * aX.mValue[iB];
         }
      }
      // Store the sum in the destination array.
      aY.mValue[i] = tSum;
   }
}
}//namespace