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
#include "dspHistoryFilterNoncausal.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryFilterNoncausal::HistoryFilterNoncausal(HistoryFilterParms& aParms)
{
   // Store.
   mParms = aParms;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryFilterNoncausal::show()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize the causal filter, based on the parms.

void HistoryFilterNoncausal::initializeCausalFilter()
{
   switch (mParms.mCausalType)
   {
   case HistoryFilterParms::cCausalButterworthLP:
   {
      // Initialize the filter according to the parameters.
      mFilter.initialize(
         mParms.mFilterOrder,
         mParms.mFs,
         mParms.mFc);
   }
   break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply the linear operator from the input to the output. F:X->Y
// This is the identity operator.

void HistoryFilterNoncausal::operate(History& aX, History& aY)
{
   //***************************************************************************
   // Initialize the filter, based on the parms.

   initializeCausalFilter();

   //***************************************************************************
   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.

   aX.createTimeClone(aY);

   //***************************************************************************
   // Locals

   int tP = aX.mNumSamples;

   //***************************************************************************
   // Create a temp array to store filtered values from the forward loop.

   double* tYForward = new double[tP];

   //***************************************************************************
   // Execute a forward loop to calculate the causally filtered values of the
   // input array.Store the filtered values in the temp array.

   // Forward loop. Progress forward in time.
   for (int i = 0; i < tP; i++)
   {
      // Read the sample value from the source array.
      double tX = aX.mValue[i];
      // Filter the value.
      double tY = mFilter.put(tX);
      // Write the filtered value to the temp forward array.
      tYForward[i] = tY;
   }

   //***************************************************************************
   // Execute a backward loop to calculate the causally filtered values of the
   // previously filtered forward array.Store the filtered values in the
   // destination array.

   // Backward loop. Progress backward in time. Time reversal.
   for (int i = tP-1; i >= 0; i--)
   {
      // Read the sample value from the temp forward array.
      double tX = tYForward[i];
      // Filter the value.
      double tY = mFilter.put(tX);
      // Write the filtered value to the destination.
      aY.mValue[i] = tY;
   }

   //***************************************************************************
   // Delete the temp array.

   delete tYForward;
}
}//namespace