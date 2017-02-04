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
// Initialize the causal filter, based on the parms.

void HistoryFilterCausal::initializeCausalFilter()
{
   switch (mParms.mCausalType)
   {
   case HistoryFilterParms::cCausalButterworthLP:
   {
      mButterworth.initialize(
         mParms.mFilterOrder,
         mParms.mFs,
         mParms.mFc);
   }
   break;
   case HistoryFilterParms::cCausalAlphaOne:
   {
      mAlphaOne.initializeFromLambda(
         mParms.mAlphaLambda);
   }
   break;
   case HistoryFilterParms::cCausalAlphaTwo:
   {
      mAlphaTwo.initializeFromLambda(
         mParms.mAlphaLambda,
         mParms.mAlphaDT);
   }
   break;
   case HistoryFilterParms::cCausalAlphaThree:
   {
      mAlphaThree.initializeFromLambda(
         mParms.mAlphaLambda,
         mParms.mAlphaDT);
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

void HistoryFilterCausal::operate(History& aX, History& aY)
{
   //***************************************************************************
   // Initialize the filter, based on the parms.

   initializeCausalFilter();

   //***************************************************************************
   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.

   aX.createTimeClone(aY);

   //***************************************************************************
   // Execute a loop to filter the input to the output.
   
   // Locals
   int tP = aX.mNumSamples;

   // For all of the samples in the source and destination arrays.
   for (int i = 0; i < tP; i++)
   {
      // Read the sample value from the source.
      double tX = aX.mValue[i];
      double tY = 0.0;
      // Filter the value.
      switch (mParms.mCausalType)
      {
      case HistoryFilterParms::cCausalButterworthLP:
      {
         tY = mButterworth.put(tX);
      }
      break;
      case HistoryFilterParms::cCausalAlphaOne:
      {
         tY = mAlphaOne.put(tX);
      }
      break;
      case HistoryFilterParms::cCausalAlphaTwo:
      {
         tY = mAlphaTwo.put(tX);
      }
      break;
      case HistoryFilterParms::cCausalAlphaThree:
      {
         tY = mAlphaThree.put(tX);
      }
      break;
      }
      // Write the filtered value to the destination.
      aY.mValue[i] = tY;
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

void HistoryFilterCausal::operate(History& aX, History& aY,History& aDY)
{
   //***************************************************************************
   // Initialize the filter, based on the parms.

   initializeCausalFilter();

   //***************************************************************************
   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.

   aX.createTimeClone(aY);
   aX.createTimeClone(aDY);

   //***************************************************************************
   // Execute a loop to filter the input to the output.
   
   // Locals
   int tP = aX.mNumSamples;

   // For all of the samples in the source and destination arrays.
   for (int i = 0; i < tP; i++)
   {
      // Read the sample value from the source.
      double tX = aX.mValue[i];
      double tY = 0.0;
      double tDY = 0.0;
      // Filter the value.
      switch (mParms.mCausalType)
      {
      case HistoryFilterParms::cCausalButterworthLP:
      {
         tY = mButterworth.put(tX);
      }
      break;
      case HistoryFilterParms::cCausalAlphaOne:
      {
         tY = mAlphaOne.put(tX);
      }
      break;
      case HistoryFilterParms::cCausalAlphaTwo:
      {
         mAlphaTwo.put(tX);
         tY  = mAlphaTwo.mXX;
         tDY = mAlphaTwo.mXV;

      }
      break;
      case HistoryFilterParms::cCausalAlphaThree:
      {
         mAlphaThree.put(tX);
         tY  = mAlphaThree.mXX;
         tDY = mAlphaThree.mXV;
      }
      break;
      }
      // Write the filtered value to the destination.
      aY.mValue[i]  = tY;
      aDY.mValue[i] = tDY;
   }
}
}//namespace