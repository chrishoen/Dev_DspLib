/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dsp_math.h"
#include "dspHistoryFilterCausal.h"

#pragma warning( disable : 4244)

namespace Dsp
{


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
      if (mParms.mAlphaStepTime > 0)
      {
         mAlphaOne.initializeFromStep(
            1/mParms.mFs,
            mParms.mAlphaStepTime,
            mParms.mAlphaStepThresh);
      }
      else if (mParms.mAlphaLambda > 0)
      {
         mAlphaOne.initializeFromLambda(
            mParms.mAlphaLambda);
      }
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
   case HistoryFilterParms::cCausalAlphaStdDev:
   {
      if (mParms.mAlphaStepTime > 0)
      {
         mAlphaStdDev.initializeFromStep(
            1/mParms.mFs,
            mParms.mAlphaStepTime,
            mParms.mAlphaStepThresh);
      }
      else if (mParms.mAlphaLambda > 0)
      {
         mAlphaStdDev.initializeFromLambda(
            mParms.mAlphaLambda);
      }
   }
   break;
   case HistoryFilterParms::cCausalAlphaAbsDev:
   {
      if (mParms.mAlphaStepTime > 0)
      {
         mAlphaAbsDev.initializeFromStep(
            1/mParms.mFs,
            mParms.mAlphaStepTime,
            mParms.mAlphaStepThresh);
      }
      else if (mParms.mAlphaLambda > 0)
      {
         mAlphaAbsDev.initializeFromLambda(
            mParms.mAlphaLambda);
      }
   }
   break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put an input to the filter, return the output.

void HistoryFilterCausal::putToFilter(double aInput, double* aOutput)
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
   case HistoryFilterParms::cCausalAlphaStdDev:
   {
      *aOutput = 0.0;
      mAlphaStdDev.put(aInput);
      switch (mParms.mAlphaSelect)
      {
      case HistoryFilterParms::cAlphaSelectEX:
      {
         *aOutput = mAlphaStdDev.mEX;
      }
      break;
      case HistoryFilterParms::cAlphaSelectUX:
      {
         *aOutput = mAlphaStdDev.mUX;
      }
      break;
      }
   }
   break;
   case HistoryFilterParms::cCausalAlphaAbsDev:
   {
      *aOutput = 0.0;
      mAlphaAbsDev.put(aInput);
      switch (mParms.mAlphaSelect)
      {
      case HistoryFilterParms::cAlphaSelectEX:
      {
         *aOutput = mAlphaAbsDev.mEX;
      }
      break;
      case HistoryFilterParms::cAlphaSelectUX:
      {
         *aOutput = mAlphaAbsDev.mUX;
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

void HistoryFilterCausal::putToFilter(double aInput, double* aOutput1, double* aOutput2)
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
   case HistoryFilterParms::cCausalAlphaStdDev:
   {
      mAlphaStdDev.put(aInput);
      *aOutput1 = mAlphaStdDev.mEX;
      *aOutput2 = mAlphaStdDev.mUX;
   }
   break;
   case HistoryFilterParms::cCausalAlphaAbsDev:
   {
      mAlphaAbsDev.put(aInput);
      *aOutput1 = mAlphaAbsDev.mEX;
      *aOutput2 = mAlphaAbsDev.mUX;
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
   //***************************************************************************
   //***************************************************************************
   // Initialize the filter, based on the parms.

   initializeCausalFilter();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.

   aX.createTimeClone(aY);

   //***************************************************************************
   //***************************************************************************
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
      putToFilter(tX,&tY);
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
// Apply the linear operator from the input to the output. F:X->Y1,,Y2

void HistoryFilterCausal::operate(History& aX, History& aY1,History& aY2)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the filter, based on the parms.

   initializeCausalFilter();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.

   aX.createTimeClone(aY1);
   aX.createTimeClone(aY2);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Execute a loop to filter the input to the output.
   
   // Locals
   int tP = aX.mNumSamples;

   // For all of the samples in the source and destination arrays.
   for (int i = 0; i < tP; i++)
   {
      // Read the sample value from the source.
      double tX = aX.mValue[i];
      double tY1 = 0.0;
      double tY2 = 0.0;
      // Filter the value.
      putToFilter(tX,&tY1,&tY2);
      // Write the filtered value to the destination.
      aY1.mValue[i] = tY1;
      aY2.mValue[i] = tY2;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace