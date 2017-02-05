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
      mButterworth.initialize(
         mParms.mFilterOrder,
         mParms.mFs,
         mParms.mFc);
   }
   break;
   case HistoryFilterParms::cCausalAlphaOne:
   {
      mAlphaOne.initialize(
         mParms.mAlphaLambda);
   }
   break;
   case HistoryFilterParms::cCausalAlphaTwo:
   {
      mAlphaTwo.initialize(
         mParms.mAlphaLambda,
         mParms.mAlphaDT);
   }
   break;
   case HistoryFilterParms::cCausalAlphaThree:
   {
      mAlphaThree.initialize(
         mParms.mAlphaLambda,
         mParms.mAlphaDT);
   }
   break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put an input to the filter, return the output.

void HistoryFilterNoncausal::putToFilterForward(double aInput, double* aOutput)
{
   switch (mParms.mCausalType)
   {
   case HistoryFilterParms::cCausalButterworthLP:
   {
      *aOutput = mButterworth.put(aInput);
   }
   break;
   case HistoryFilterParms::cCausalAlphaOne:
   {
      *aOutput = mAlphaOne.put(aInput);
   }
   break;
   case HistoryFilterParms::cCausalAlphaTwo:
   {
      mAlphaTwo.put(aInput);
      *aOutput = mAlphaTwo.mXX;
   }
   break;
   case HistoryFilterParms::cCausalAlphaThree:
   {
      mAlphaThree.put(aInput);
      *aOutput = mAlphaThree.mXX;
   }
   break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put an input to the filter, return the output.

void HistoryFilterNoncausal::putToFilterBackward(double aInput, double* aOutput)
{
   switch (mParms.mCausalType)
   {
   case HistoryFilterParms::cCausalButterworthLP:
   {
      *aOutput = mButterworth.put(aInput);
   }
   break;
   case HistoryFilterParms::cCausalAlphaOne:
   {
      *aOutput = mAlphaOne.put(aInput);
   }
   break;
   case HistoryFilterParms::cCausalAlphaTwo:
   {
      *aOutput = 0.0;
      mAlphaTwo.put(aInput);
      switch (mParms.mAlphaSelect)
      {
      case HistoryFilterParms::cAlphaSelectXX:
      {
         *aOutput = mAlphaTwo.mXX;
      }
      break;
      case HistoryFilterParms::cAlphaSelectXV:
      {
         *aOutput = mAlphaTwo.mXV;
      }
      break;
      }
   }
   break;
   case HistoryFilterParms::cCausalAlphaThree:
   {
      *aOutput = 0.0;
      mAlphaThree.put(aInput);
      switch (mParms.mAlphaSelect)
      {
      case HistoryFilterParms::cAlphaSelectXX:
      {
         *aOutput = mAlphaThree.mXX;
      }
      break;
      case HistoryFilterParms::cAlphaSelectXV:
      {
         *aOutput = mAlphaThree.mXV;
      }
      break;
      case HistoryFilterParms::cAlphaSelectXA:
      {
         *aOutput = mAlphaThree.mXA;
      }
      break;
      }
   }
   break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put an input to the filter, return the output.

void HistoryFilterNoncausal::putToFilterBackward(double aInput, double* aOutput1, double* aOutput2)
{
   switch (mParms.mCausalType)
   {
   case HistoryFilterParms::cCausalButterworthLP:
   {
      *aOutput1 = mButterworth.put(aInput);
      *aOutput2 = 0.0;
   }
   break;
   case HistoryFilterParms::cCausalAlphaOne:
   {
      *aOutput1 = mAlphaOne.put(aInput);
      *aOutput2 = 0.0;
   }
   break;
   case HistoryFilterParms::cCausalAlphaTwo:
   {
      mAlphaTwo.put(aInput);
      *aOutput1 = mAlphaTwo.mXX;
      *aOutput2 = mAlphaTwo.mXV;
   }
   break;
   case HistoryFilterParms::cCausalAlphaThree:
   {
      mAlphaThree.put(aInput);
      *aOutput1 = mAlphaThree.mXX;
      *aOutput2 = mAlphaThree.mXV;
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

   // For all of the samples in the source and destination arrays.
   for (int i = 0; i < tP; i++)
   {
      // Read the sample value from the source.
      double tX = aX.mValue[i];
      double tY = 0.0;
      // Filter the value.
      putToFilterForward(tX,&tY);
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
      // Read the sample value from the source.
      double tX = tYForward[i];
      double tY = 0.0;
      // Filter the value.
      putToFilterBackward(tX,&tY);
      // Write the filtered value to the destination.
      aY.mValue[i] = tY;
   }

   //***************************************************************************
   // Delete the temp array.

   delete tYForward;
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply the linear operator from the input to the output. F:X->Y
// This is the identity operator.

void HistoryFilterNoncausal::operate(History& aX, History& aY1, History& aY2)
{
   //***************************************************************************
   // Initialize the filter, based on the parms.

   initializeCausalFilter();

   //***************************************************************************
   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.

   aX.createTimeClone(aY1);
   aX.createTimeClone(aY2);

   //***************************************************************************
   // Locals

   int tP = aX.mNumSamples;

   //***************************************************************************
   // Create a temp array to store filtered values from the forward loop.

   double* tYForward = new double[tP];

   //***************************************************************************
   // Execute a forward loop to calculate the causally filtered values of the
   // input array.Store the filtered values in the temp array.

   // For all of the samples in the source and destination arrays.
   for (int i = 0; i < tP; i++)
   {
      // Read the sample value from the source.
      double tX = aX.mValue[i];
      double tY = 0.0;
      // Filter the value.
      putToFilterForward(tX,&tY);
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
      // Read the sample value from the source.
      double tX = tYForward[i];
      double tY1 = 0.0;
      double tY2 = 0.0;
      // Filter the value.
      putToFilterBackward(tX,&tY1,&tY2);
      // Write the filtered value to the destination.
      aY1.mValue[i] = tY1;
      aY2.mValue[i] = tY2;
   }

   //***************************************************************************
   // Delete the temp array.

   delete tYForward;
}
}//namespace