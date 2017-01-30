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
#include "dspStatistics.h"
#include "dspHistoryOps.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy X to Y, X->Y.

void historyCopy(
   History& aX,
   History& aY)
{
   // Initialize Y with the size of X.
   aY.initialize(aX.mNumSamples);

   // Start Y.
   aY.startWrite();

   // Loop through all of the samples in X.
   for (int k = 0; k < aX.mNumSamples; k++)
   {
      double tTimeX  = 0.0;
      double tValueX = 0.0;
      
      // Get the sample from X.
      aX.readSampleAtIndex(k,&tTimeX,&tValueX);

      // Put the sample to Y.
      aY.writeSample(tTimeX,tValueX);
   }

   // Finish Y.
   aY.finishWrite();
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy X to Y with values interpolated to a delay, X->Y.

void historyCopyWithDelay(
   History& aX,
   double   aDelay,
   History& aY)
{
   // Initialize Y with the size of X.
   aY.initialize(aX.mNumSamples);

   // Start Y.
   aY.startWrite();

   // Loop through all of the samples in X.
   for (int k = 0; k < aX.mNumSamples; k++)
   {
      double tTimeX  = 0.0;
      double tValueX = 0.0;
      
      // Get the sample from X.
      aX.readSampleAtIndex(k,&tTimeX,&tValueX);

      tTimeX += aDelay;

      // Put the sample to Y.
      aY.writeSample(tTimeX,tValueX);
   }

   // Finish Y.
   aY.finishWrite();
}
}//namespace