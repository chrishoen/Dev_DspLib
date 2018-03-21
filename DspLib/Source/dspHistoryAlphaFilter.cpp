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

}

void HistoryAlphaFilter::initialize(double aAlpha)
{

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
   // input array.Store the filtered values in the temp array.

   // For all of the samples in the source and destination arrays.
   for (int i = 0; i < tP; i++)
   {
      // Read the sample value from the source.
      double tX = aX.mValue[i];
      double tY = 0.0;
      // Write the filtered value to the temp forward array.
      aY.mValue[i] = tY;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Execute a backward loop to calculate the causally filtered values of the
   // previously filtered forward array.Store the filtered values in the
   // destination array.

   // Backward loop. Progress backward in time. Time reversal.
   for (int i = tP-1; i >= 0; i--)
   {
      // Read the sample value from the source.
      double tX = aX.mValue[i];
      double tY = 0.0;
      // Write the filtered value to the temp forward array.
      aY.mValue[i] = tY;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace