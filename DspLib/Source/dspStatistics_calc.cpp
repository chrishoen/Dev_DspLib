/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <string.h>

#include "prnPrint.h"
#include "logFiles.h"

#include "dsp_math.h"
#include "dspStatistics.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

TrialStatistics::TrialStatistics()
{
   startTrial();
}

void TrialStatistics::startTrial(double aXLimit)
{
   mCount = 0;
   mXLimit = aXLimit;
   mXLimitFlag = aXLimit!=0.0;
   mX = 0.0;

   mEX = 0.0;
   mUX = 0.0;
   mMean   = 0.0;
   mStdDev = 0.0;
   mMinX = 0.0;
   mMaxX = 0.0;
   mExtX = 0.0;
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

void TrialStatistics::put(double aX)
{
   //--------------------------------------------------------------------------- 
   // Store current input

   if (mXLimitFlag)
   {
      if (aX < -mXLimit) return;
      if (aX >  mXLimit) return;
   }

   mX = aX;
   mCount++;

   //--------------------------------------------------------------------------- 
   // Update min and max

   // If first in period, set to current input  
   if (mCount==1)
   {
      mMinX = mX;
      mMaxX = mX;
      mExtX = mX;
   }
   // Else, calculate min and max
   else
   {
      if (mX < mMinX) mMinX = mX;
      if (mX > mMaxX) mMaxX = mX;
      if (fabs(mX) > fabs(mExtX)) mExtX = mX;
   }

   //--------------------------------------------------------------------------- 
   // Calculate sums

      mOLDelta =  mX - mOLMean;
      mOLMean  += mOLDelta/mCount;
      mOLM2    += mOLDelta*(mX - mOLMean);

      mXSum += mX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::finishTrial()
{
   // Calculate results for mean and standard deviation

   // Expectation (mean) of X
   mEX = mOLMean;

   // Variance of X
   if (mCount < 2)
   {
      mVariance = 0.0;
   }
   else
   {
      mVariance = mOLM2/(mCount);
   }

   // Uncertainty (stddev) of X
   if (mVariance > 0.0f)
   {
      mUX = sqrt(mVariance);
   }
   else
   {
      mUX = 0.0f;
   }

   // Store
   mMean   = mEX;
   mStdDev = mUX;

   mXMean = mXSum/mCount;

   // More
   mSX = mEX - mExtX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

