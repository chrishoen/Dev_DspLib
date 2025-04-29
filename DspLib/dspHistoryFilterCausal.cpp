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
      if (mParms.mAlphaAlpha > 0)
      {
         mAlphaOne.initializeFromAlpha(
            mParms.mAlphaAlpha);
      }
      else if (mParms.mAlphaNoiseRatio > 0)
      {
         mAlphaOne.initializeFromNoiseRatio(
            mParms.mAlphaNoiseRatio,
            mParms.mAlphaDT);
      }
      else if (mParms.mAlphaStepTime > 0)
      {
         mAlphaOne.initializeFromStep(
            mParms.mAlphaDT,
            mParms.mAlphaStepTime,
            mParms.mAlphaStepThresh);
      }
   }
   break;
   case HistoryFilterParms::cCausalAlphaTwo:
   {
      if (mParms.mAlphaAlpha > 0)
      {
         mAlphaTwo.initializeFromAlpha(
            mParms.mAlphaAlpha,
            mParms.mAlphaDT);
      }
      else if (mParms.mAlphaNoiseRatio > 0)
      {
         mAlphaTwo.initializeFromNoiseRatio(
            mParms.mAlphaNoiseRatio,
            mParms.mAlphaDT);
      }
   }
   break;
   case HistoryFilterParms::cCausalAlphaThree:
   {
      if (mParms.mAlphaAlpha > 0)
      {
         mAlphaThree.initializeFromAlpha(
            mParms.mAlphaAlpha,
            mParms.mAlphaDT);
      }
      else if (mParms.mAlphaNoiseRatio > 0)
      {
         mAlphaThree.initializeFromNoiseRatio(
            mParms.mAlphaNoiseRatio,
            mParms.mAlphaDT);
      }
   }
   break;
   case HistoryFilterParms::cCausalAlphaStdDev:
   {
      if (mParms.mAlphaAlpha > 0)
      {
         mAlphaStdDev.initializeFromAlpha(
            mParms.mAlphaAlpha);
      }
      else if (mParms.mAlphaNoiseRatio > 0)
      {
         mAlphaStdDev.initializeFromNoiseRatio(
            mParms.mAlphaNoiseRatio,
            mParms.mAlphaDT);
      }
      else if (mParms.mAlphaStepTime > 0)
      {
         mAlphaStdDev.initializeFromStep(
            mParms.mAlphaDT,
            mParms.mAlphaStepTime,
            mParms.mAlphaStepThresh);
      }
   }
   break;
   case HistoryFilterParms::cCausalAlphaAbsDev:
   {
      if (mParms.mAlphaAlpha > 0)
      {
         mAlphaAbsDev.initializeFromAlpha(
            mParms.mAlphaAlpha);
      }
      else if (mParms.mAlphaNoiseRatio > 0)
      {
         mAlphaAbsDev.initializeFromNoiseRatio(
            mParms.mAlphaNoiseRatio,
            mParms.mAlphaDT);
      }
      else if (mParms.mAlphaStepTime > 0)
      {
         mAlphaAbsDev.initializeFromStep(
            mParms.mAlphaDT,
            mParms.mAlphaStepTime,
            mParms.mAlphaStepThresh);
      }
   }
   break;
   case HistoryFilterParms::cCausalSlidingMean:
   {
      mSlidingMean.reset();
   }
   break;
   case HistoryFilterParms::cCausalBiasEstimator:
   {
      mBiasEstimator.reset();
      mBiasEstimator.mLimitHi = mParms.mLimitHi;
      mBiasEstimator.mLimitLo = mParms.mLimitLo;
      mBiasEstimator.mThreshDev= mParms.mThreshDev;
      mBiasEstimator.mAlphaBias.initializeFromStep(
         mParms.mAlphaDT,
         mParms.mAlphaStepTime,
         mParms.mAlphaStepThresh);
      mBiasEstimator.mAlphaX.initializeFromStep(
         mParms.mAlphaDT,
         mParms.mAlphaStepTimeDev,
         mParms.mAlphaStepThresh);
      mBiasEstimator.initialize();
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
   case HistoryFilterParms::cCausalSlidingMean:
   {
      *aOutput = 0.0;
      mSlidingMean.doPut(aInput);
      *aOutput = mSlidingMean.mMean;
   }
   break;
   case HistoryFilterParms::cCausalBiasEstimator:
   {
      *aOutput = 0.0;
      mBiasEstimator.put(aInput);
      *aOutput = mBiasEstimator.mBias;
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
   case HistoryFilterParms::cCausalSlidingMean:
   {
      mSlidingMean.doPut(aInput);
      *aOutput1 = mSlidingMean.mMean;
      *aOutput2 = mSlidingMean.mDelta;
   }
   break;
   case HistoryFilterParms::cCausalBiasEstimator:
   {
      mBiasEstimator.put(aInput);
      *aOutput1 = mBiasEstimator.mMean;
      *aOutput2 = mBiasEstimator.mBias;
   }
   break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put an input to the filter, return the output.

void HistoryFilterCausal::putToFilter(
   double aInput, double* aOutput1, double* aOutput2, double* aOutput3)
{
   switch (mParms.mCausalType)
   {
   case HistoryFilterParms::cCausalButterworthLP:
   {
      *aOutput1 = mButterworth.put(aInput);
      *aOutput2 = 0.0;
      *aOutput3 = 0.0;
   }
   break;
   case HistoryFilterParms::cCausalAlphaOne:
   {
      *aOutput1 = mAlphaOne.put(aInput);
      *aOutput2 = 0.0;
      *aOutput3 = 0.0;
   }
   break;
   case HistoryFilterParms::cCausalAlphaTwo:
   {
      mAlphaTwo.put(aInput);
      *aOutput1 = mAlphaTwo.mXX;
      *aOutput2 = mAlphaTwo.mXV;
      *aOutput3 = 0.0;
   }
   break;
   case HistoryFilterParms::cCausalAlphaThree:
   {
      mAlphaThree.put(aInput);
      *aOutput1 = mAlphaThree.mXX;
      *aOutput2 = mAlphaThree.mXV;
      *aOutput3 = mAlphaThree.mXA;
   }
   break;
   case HistoryFilterParms::cCausalAlphaStdDev:
   {
      mAlphaStdDev.put(aInput);
      *aOutput1 = mAlphaStdDev.mEX;
      *aOutput2 = mAlphaStdDev.mUX;
      *aOutput3 = 0.0;
   }
   break;
   case HistoryFilterParms::cCausalAlphaAbsDev:
   {
      mAlphaAbsDev.put(aInput);
      *aOutput1 = mAlphaAbsDev.mEX;
      *aOutput2 = mAlphaAbsDev.mUX;
      *aOutput3 = 0.0;
   }
   break;
   case HistoryFilterParms::cCausalSlidingMean:
   {
      mSlidingMean.doPut(aInput);
      *aOutput1 = mSlidingMean.mMean;
      *aOutput2 = mSlidingMean.mDelta;
      *aOutput3 = 0.0;
   }
   break;
   case HistoryFilterParms::cCausalBiasEstimator:
   {
      mBiasEstimator.put(aInput);
      *aOutput1 = mBiasEstimator.mMean;
      *aOutput2 = mBiasEstimator.mAbsDev;
      *aOutput3 = mBiasEstimator.mBias;
   }
   break;
   }
}

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
// Apply the linear operator from the input to the output. F:X->Y1,,Y2

void HistoryFilterCausal::operate(History& aX, History& aY1,History& aY2,History& aY3)
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
   aX.createTimeClone(aY3);

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
      double tY3 = 0.0;
      // Filter the value.
      putToFilter(tX,&tY1,&tY2,&tY3);
      // Write the filtered value to the destination.
      aY1.mValue[i] = tY1;
      aY2.mValue[i] = tY2;
      aY3.mValue[i] = tY3;
   }
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace