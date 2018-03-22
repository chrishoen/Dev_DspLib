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
#include "dspHistoryAlphaFilter.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryAlphaFilter::HistoryAlphaFilter()
{

}

HistoryAlphaFilter::HistoryAlphaFilter(double aAlpha)
{
   mAlphaOne.initializeFromLambda(aAlpha);
}

void HistoryAlphaFilter::initialize(double aAlpha)
{
   mAlphaOne.initializeFromLambda(aAlpha);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply the linear operator from the input to the output. F:X->Y
// This is the identity operator.

void HistoryAlphaFilter::operate(History& aX, History& aY)
{
   //***************************************************************************
   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.

   aX.createTimeClone(aY);

   //***************************************************************************
   // Locals

   int tP = aX.mNumSamples;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Execute a forward loop to calculate the causally filtered values of the
   // input array into the output array.

   // Restart the alpha filter for first sample.
   mAlphaOne.setFirst();

   // For all of the samples in the source and destination arrays, loop
   // forward in time.
   for (int i = 0; i < tP; i++)
   {
      // Write the filtered value to the output array.
      aY.mValue[i] = mAlphaOne.put(aX.mValue[i]);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Execute a backward loop to calculate the causally filtered values of the
   // previously filtered output array back into the output array.

   // Restart the alpha filter for first sample.
   mAlphaOne.setFirst();

   // For all of the samples in the destination array, loop backward in time.
   // Backward loop. Progress backward in time. Time reversal.
   for (int i = tP-1; i >= 0; i--)
   {
      // Write the filtered value to the output array.
      aY.mValue[i] = mAlphaOne.put(aY.mValue[i]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace