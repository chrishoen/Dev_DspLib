/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dsp_functions.h"
#include "dsp_math.h"
#include "dspStatistics.h"
#include "dspHistoryOperDerivOne.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryOperDerivOne::HistoryOperDerivOne(HistoryOperParms& aParms)
{
   BaseClass::initialize(aParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryOperDerivOne::show()
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

void HistoryOperDerivOne::calculateCoefficients()
{
   // Locals.
   mC[0] = 0.0;
   double tH = mParms.mH;

   // Select on filter order.
   switch (mParms.mN)
   {
   case 5:
   {
      double tDenom = (8.0*tH);
      mC[1] =   2.0/tDenom;
      mC[2] =   1.0/tDenom;
   }
   break;
   case 7:
   {
      double tDenom = (32.0*tH);
      mC[1] =   5.0/tDenom;
      mC[2] =   4.0/tDenom;
      mC[3] =   1.0/tDenom;
   }
   break;
   case 9:
   {
      double tDenom = (128.0*tH);
      mC[1] =  14.0/tDenom;
      mC[2] =  14.0/tDenom;
      mC[3] =   6.0/tDenom;
      mC[4] =   1.0/tDenom;
   }
   break;
   case 11:
   {
      double tDenom = (512.0*tH);
      mC[1] =  42.0/tDenom;
      mC[2] =  48.0/tDenom;
      mC[3] =  27.0/tDenom;
      mC[4] =   8.0/tDenom;
      mC[5] =   1.0/tDenom;
   }
   break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply the linear operator from the input to the output. F:X->Y.
// This calculates the first derivative using a central difference method
// based on the Holoborodko algorithm for regular time intervals.

void HistoryOperDerivOne::operate(History& aX, History& aY)
{
   printf("HistoryOperDerivOne::operate %d\n",mParms.mFilterOrder);

   // Calculate the central difference filter coefficents, based on the parms.
   calculateCoefficients();

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
      double tSum = 0.0;
      for (int k = 1; k <= tM; k++)
      {
         // Calculate the forward  array index, trim at the end.
         int iF = dsp_imin(i + k,tP-1);
         // Calculate the backward array index, trim at the beginning.
         int iB = dsp_imax(i - k,0);
         // Accumulate the sum from forward  source samples and coefficients.
         tSum += mC[k]*aX.mValue[iF];
         // Accumulate the sum from backward source samples and coefficients.
         tSum -= mC[k]*aX.mValue[iB];
      }
      // Store the sum in the destination array.
      aY.mValue[i] = tSum;
   }
}
}//namespace