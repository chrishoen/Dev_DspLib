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
#include "dspHistoryGenBase.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryGenBase::HistoryGenBase()
{
   reset();
}

void HistoryGenBase::reset()
{
   mFs = 1.0;
   mTs = 1.0 / mFs;

   mDuration = 10.0;
   mNumSamples = (int)(mDuration * mFs);

   mEX = 0.0;
   mUX = 1.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize variables. Initialize the history. Initialize the history time
// array.

void HistoryGenBase::initialize(History& aHistory)
{
   // Initialize variables.
   mTs = 1.0 / mFs;
   mNumSamples = (int)(mDuration * mFs);

   // Initialize the history.
   aHistory.initialize(mNumSamples);

   // Initialize the history to zeros.
   double tTimeSum=0.0;
   aHistory.startHistory();
   for (int k = 0; k < mNumSamples; k++)
   {
      aHistory.writeSample(tTimeSum,0.0);
      tTimeSum += mTs;
   }
   aHistory.finishHistory();
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryGenBase::show()
{
   printf("mDuration    %10.4f\n",mDuration);
   printf("mNumSamples  %10d\n",  mNumSamples);
   printf("mFs          %10.4f\n",mFs);
   printf("mTs          %10.4f\n",mTs);
   printf("mEX          %10.4f\n",mEX);
   printf("mUX          %10.4f\n",mUX);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void HistoryGenBase::normalize(History& aHistory)
{
   //---------------------------------------------------------------------------
   // Statistics.

   TrialStatistics  tTrialStatistics;
   tTrialStatistics.startTrial();

   for (int k = 0; k < mNumSamples; k++)
   {
      tTrialStatistics.put(aHistory.mValue[k]);
   }

   tTrialStatistics.finishTrial();

   //---------------------------------------------------------------------------
   // Normalize to get the desired expectation and uncertainty.

   double tScale = 1.0;
   double tEX = tTrialStatistics.mEX;
   double tUX = tTrialStatistics.mUX;

   if (tUX != 0.0) tScale = mUX/tUX;

   for (int k = 0; k < mNumSamples; k++)
   {
      aHistory.mValue[k] = tScale*(aHistory.mValue[k] - tEX) + mEX;
   }
}

}//namespace