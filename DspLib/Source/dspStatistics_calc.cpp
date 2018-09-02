/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

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
   mDropCount = 0;
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
   mTimeMinX = 0.0;
   mTimeMaxX = 0.0;
   mTimeExtX = 0.0;
   mSX = 0.0;
   mRms = 0.0;

   mOLMean = 0.0;
   mOLM2 = 0.0;
   mOLDelta = 0.0;

   mXSum = 0.0;
   mXMean = 0.0;
   mXsqSum = 0.0;
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put input value and calculate intermediate variables.

void TrialStatistics::put(double aX)
{
   put(aX,0.0);
}

void TrialStatistics::drop()
{
   mDropCount++;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put input value with the time that it occured and calculate
// intermediate variables

void TrialStatistics::put(double aX,double aTime)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Store current input. Ignore outliers.

   if (mXLimitFlag)
   {
      if (aX < -mXLimit) return;
      if (aX >  mXLimit) return;
   }

   mX = aX;
   mCount++;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Update min and max

   // If first then set to current input  
   if (mCount==1)
   {
      mMinX = mX;
      mTimeMinX = aTime;

      mMaxX = mX;
      mTimeMaxX = aTime;

      mExtX = mX;
      mTimeExtX = aTime;
   }
   // Else, calculate min and max
   else
   {
      if (mX < mMinX)
      {
         mMinX = mX;
         mTimeMinX = aTime;
      }

      if (mX > mMaxX)
      {
         mMaxX = mX;
         mTimeMaxX = aTime;
      }

      if (fabs(mX) > fabs(mExtX))
      {
         mExtX = mX;
         mTimeExtX = aTime;
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Calculate sums for the online algorithm

   mOLDelta =  mX - mOLMean;
   mOLMean  += mOLDelta/mCount;
   mOLM2    += mOLDelta*(mX - mOLMean);

   mXSum += mX;
   mXsqSum += mX*mX;
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

   // More
   if (mCount > 0)
   {
      mRms = sqrt(mXsqSum/mCount);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

