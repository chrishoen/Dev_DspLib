/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <math.h>
#include <string.h>

#include "dspTrialStatistics.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

TrialStatistics::TrialStatistics()
{
   mMaxMaxX = -1E9;
   startTrial();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Start trial with optional outlier limit.

void TrialStatistics::startTrial(double aXLimit)
{
   mPutCount = 0;
   mXLimit = aXLimit;
   mXLimitFlag = aXLimit!=0.0;
   mX = 0.0;

   mEX = 0.0;
   mUX = 0.0;
   mMean   = 0.0;
   mStdDev = 0.0;
   mMinX = 0.0;
   mMaxX = 0.0;
   mVariance = 0.0;

   mOLMean = 0.0;
   mOLM2 = 0.0;
   mOLDelta = 0.0;

   mXSum = 0.0;
   mXMean = 0.0;
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put input value.

void TrialStatistics::put(double aX)
{
   // Ignore outliers.
   if (mXLimitFlag)
   {
      if (aX < -mXLimit) return;
      if (aX >  mXLimit) return;
   }

   // Store current input.
   mX = aX;
   mPutCount++;

   // If first sample.
   if (mPutCount==1)
   {
      // Initialize min and max.
      mMinX = mX;
      mMaxX = mX;
   }
   // If not first sample.
   else
   {
      // Update min and max
      if (mX < mMinX) mMinX = mX;
      if (mX > mMaxX) mMaxX = mX;
      if (mX > mMaxMaxX) mMaxMaxX = mX;
   }

   // Calculate sums.
   mOLDelta =  mX - mOLMean;
   mOLMean  += mOLDelta/mPutCount;
   mOLM2    += mOLDelta*(mX - mOLMean);
   mXSum += mX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finish trial, calculate results.

void TrialStatistics::finishTrial()
{
   // Calculate results for mean and standard deviation

   // Expectation (mean) of X
   mEX = mOLMean;

   // Variance of X
   if (mPutCount < 2)
   {
      mVariance = 0.0;
   }
   else
   {
      mVariance = mOLM2/(mPutCount);
   }

   // Uncertainty (stddev) of X
   if (mVariance > 0)
   {
      mUX = sqrt(mVariance);
   }
   else
   {
      mUX = 0;
   }

   // Store
   mMean   = mEX;
   mStdDev = mUX;

   mXMean = mXSum/mPutCount;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::show(int aPF, char* aLabel)
{
   Prn::print(aPF, "%-10s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

