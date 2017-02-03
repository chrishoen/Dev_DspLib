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
#include "dspHistoryFilterCausal.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryFilterCausal::HistoryFilterCausal(HistoryFilterParms& aParms)
{
   // Store.
   mParms = aParms;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryFilterCausal::show()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void HistoryFilterCausal::initializeFilter()
{
   // Initialize the filter according to the parameters.
   mFilter.initialize(
      mParms.mFilterOrder,
      mParms.mFs,
      mParms.mFc);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply the linear operator from the input to the output. F:X->Y
// This is the identity operator.

void HistoryFilterCausal::operate(History& aX, History& aY)
{
   //***************************************************************************
   // Initialize the filter, based on the parms.

   switch (mParms.mCausalType)
   {
   case HistoryFilterParms::cCausalButterworthLP:
   {
      initializeFilter();
   }
   break;
   }

   //***************************************************************************
   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.

   aX.createTimeClone(aY);

   //***************************************************************************
   // Execute a loop to calculate the central difference sum to implement
   // the algorithm.

   // Locals
   int tP = aX.mNumSamples;

   // For all of the samples in the source and destination arrays.
   for (int i = 0; i < tP; i++)
   {
      // Read the sample value from the source.
      double tX = aX.mValue[i];
      // Filter the value.
      double tY = mFilter.put(tX);
      // Write the filtered value to the destination.
      aY.mValue[i] = tY;
   }
}
}//namespace