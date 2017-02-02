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
#include "dspHistoryOperFilterSavGol.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryOperFilterSavGol::HistoryOperFilterSavGol(HistoryOperParms& aParms)
{
   BaseClass::initialize(aParms);
   mBackAddFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryOperFilterSavGol::show()
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
// This coefficients are used to calculate a smoothed output.

void HistoryOperFilterSavGol::calculateCoefficientsSmoother()
{
   // Add the backward time terms.
   mBackAddFlag = true;

   // Locals.
   int N = mParms.mFilterOrder;
   int M = (N-1)/2;

   // Calculate coefficents.
   for (int k = 0; k <= M; k++)
   {
      mC[k] = 1.0/double(N);
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

void HistoryOperFilterSavGol::operate(History& aX, History& aY)
{
   //***************************************************************************
   // Calculate the central difference filter coefficents, based on the parms.
   switch (mParms.mOperType)
   {
   case HistoryOperParms::cOperSmoother:
   {
      calculateCoefficientsSmoother();
   }
   break;
   case HistoryOperParms::cOperFirstDeriv:
   {
      calculateCoefficientsFirstDerivative();
   }
   break;
   case HistoryOperParms::cOperSecondDeriv:
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