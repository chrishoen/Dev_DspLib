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

SumStatistics::SumStatistics()
{
   reset();
}

void SumStatistics::reset()
{
   // Output values
   mX = 0.0;
   mEX = 0.0;
   mUX = 0.0;
   mMean = 0.0;
   mStdDev = 0.0;
   mEXSquare = 0.0;
   mVariance = 0.0;
   mXSum = 0.0;
   mXSquareSum = 0.0;
   mCount = 0;
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void SumStatistics::add(double aX)
{
   //--------------------------------------------------------------------------- 
   // Update sums

   mXSum       += aX;
   mXSquareSum += aX*aX;
   mCount++;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SumStatistics::subtract(double aX)
{
   // Guard
   if (mCount==0)return;

   //--------------------------------------------------------------------------- 
   // Update sums

   mXSum       -= aX;
   mXSquareSum -= aX*aX;
   mCount--;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate results for mean and standard deviation

void SumStatistics::calculate()
{
   // Guard
   if (mCount==0)return;

   // Expectation (mean) of X
   mEX = mXSum / mCount;
   // Expectation of X squared
   mEXSquare = mXSquareSum / mCount;

   // Variance of X
   mVariance = mEXSquare - mEX*mEX;

   // Uncertainty (stddev) of X
   if (mVariance > 0.0f)
   {
      mUX = sqrt(mVariance);
   }
   else
   {
      mUX = 0.0;
   }

   // Store nicknames
   mMean   = mEX;
   mStdDev = mUX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SumStatistics::show()
{
   printf("%3d $$ %8.6f %8.6f\n",
      mCount,
      mEX,
      mUX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void PeriodicStatistics::initialize(int aSize)
{
   mSize = aSize;
   mFirstFlag = true;
   mX = 0.0f;
   mEndOfPeriod = false;
   mEX = 0.0f;
   mUX = 0.0f;
   mMean   = 0.0f;
   mStdDev = 0.0f;
   mMinX = 0.0f;
   mMaxX = 0.0f;
   mXSum = 0.0f;
   mXSquareSum = 0.0f;
   mCurrentMinX = 0.0f;
   mCurrentMaxX = 0.0f;
   mPutCount = 0;
   mK = 0;
}
   
//******************************************************************************

void PeriodicStatistics::put(double aX)
{
   //--------------------------------------------------------------------------- 
   // Store current input
   mX = aX;

   //--------------------------------------------------------------------------- 
   // Update min and max

   // If first in period, set to current input  
   if (mFirstFlag)
   {
      mFirstFlag = false;
      mCurrentMinX = mX;
      mCurrentMaxX = mX;
   }
   // Else, calculate min and max
   else
   {
      if (mX < mCurrentMinX) mCurrentMinX = mX;
      if (mX > mCurrentMaxX) mCurrentMaxX = mX;
   }

   //--------------------------------------------------------------------------- 
   // Update sums

   mXSum += aX;
   mXSquareSum += aX*aX;

   //--------------------------------------------------------------------------- 
   // If at the end of the period

   if (++mPutCount == mSize)
   {
      // Calculate results for mean and standard deviation

      // Expectation (mean) of X
      mEX = mXSum / mPutCount;
      // Expectation of X squared
      mEXSquare = mXSquareSum / mPutCount;

      // Variance of X
      mVariance = mEXSquare - mEX*mEX;

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

      // Latch minimum and maximum
      mMinX = mCurrentMinX;
      mMaxX = mCurrentMaxX;

      // Reset sums and counts
      mXSum = 0.0;;
      mXSquareSum = 0.0;
      mPutCount = 0;

      // Indicate end of period
      mEndOfPeriod = true;
      mFirstFlag = true;
   }
   else
   {
      // Indicate not end of period
    	mEndOfPeriod = false;
   }

   //--------------------------------------------------------------------------- 
   // Done
   mK++;
}

//******************************************************************************
void PeriodicStatistics::show()
{
   if (mEndOfPeriod)
   {
      printf("%3d %8.3f $$ %8.3f %8.3f %8.3f  %8.3f\n",
         mK,
         mX,
         mEX,
         mUX,
         mMinX,
         mMaxX);
   }
   else
   {
      printf("%3d %8.3f\n",
         mK,
         mX);
   }
}

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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::show(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-8s %5llu $$ %12.6f %12.6f %12.6f  %12.6f",
      aLabel,
      mCount,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************

void TrialStatistics::showDeg(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-8s %5llu $$ %12.6f %12.6f %12.6f  %12.6f",
      aLabel,
      mCount,
      deg(mEX),
      deg(mUX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::showEUMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-8s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************

void TrialStatistics::showDegEUMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-8s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mUX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::showEUX(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-8s $$ %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mExtX);
}

//******************************************************************************

void TrialStatistics::showDegEUX(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-8s $$ %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mUX),
      deg(mExtX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::showEMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-8s $$ %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mMinX,
      mMaxX);
}

//******************************************************************************

void TrialStatistics::showDegEMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-8s $$ %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::log(int aLogNum,char* aLabel)
{
   Log::write(aLogNum,"%-8s %5llu $$ %12.6f %12.6f %12.6f  %12.6f",
      aLabel,
      mCount,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************

void TrialStatistics::logDeg(int aLogNum,char* aLabel)
{
   Log::write(aLogNum,"%-8s %5llu $$ %12.6f %12.6f %12.6f  %12.6f",
      aLabel,
      mCount,
      deg(mEX),
      deg(mUX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logEUMM(int aLogNum,char* aLabel)
{
   Log::write(aLogNum,"%-8s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************

void TrialStatistics::logDegEUMM(int aLogNum,char* aLabel)
{
   Log::write(aLogNum,"%-8s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mUX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logEUX(int aLogNum,char* aLabel)
{
   Log::write(aLogNum,"%-8s $$ %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mExtX);
}

//******************************************************************************

void TrialStatistics::logDegEUX(int aLogNum,char* aLabel)
{
   Log::write(aLogNum,"%-8s $$ %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mUX),
      deg(mExtX));
}

//******************************************************************************

void TrialStatistics::logUX(int aLogNum)
{
   Log::write(aLogNum,"%12.6f,%12.6f,",
      mUX,
      mExtX);
}

//******************************************************************************

void TrialStatistics::logDegUX(int aLogNum)
{
   Log::write(aLogNum,"%12.6f,%12.6f,",
      deg(mUX),
      deg(mExtX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

