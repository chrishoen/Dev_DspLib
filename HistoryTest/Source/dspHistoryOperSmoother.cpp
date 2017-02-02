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
#include "dspHistoryOperSmoother.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryOperSmoother::HistoryOperSmoother(HistoryOperParms& aParms)
{
   BaseClass::initialize(aParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryOperSmoother::show()
{
   BaseClass::show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents, based on the parms.

void HistoryOperSmoother::calculateCoefficients1()
{
   // Start.
   mC[0] = 0.0;

   // Locals.
   double tH = mParms.mH;

   int N = mParms.mN;
   int M = mParms.mM;
   int m = (N-3)/2;

   double tTerm1 = 1.0/pow(2.0,double(2*m+1));
   double tTerm2 = 1.0/tH;

   for (int k = 0; k < N; k++)
   {
      mC[k] = 1.0/double(N);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply the linear operator from the input to the output. F:X->Y
// This is the identity operator.

void HistoryOperSmoother::operate(History& aX, History& aY)
{
   printf("HistoryOperSmoother::operate %d\n",mParms.mFilterOrder);

   // Calculate the central difference filter coefficents, based on the parms.
   calculateCoefficients1();

   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.
   BaseClass::createTimeClone(aX,aY);

   // Locals
   int tP = aX.mNumSamples;
   int tM = mParms.mM;

   // Execute a loop to calculate the central difference sum to implement
   // the algorithm.

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
         tSum += mC[k]*aX.mValue[iB];
      }
      // Store the sum in the destination array.
      aY.mValue[i] = tSum;
   }
}
}//namespace