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
   mParms.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryGenBase::show()
{
   mParms.show("Parms");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize member variables. Initialize the history memory for the correct
// number of samples. Set the history value array to zero and the time array
// to lenearly increasing.

void HistoryGenBase::initializeHistory(History& aHistory)
{
   // Initialize the history.
   aHistory.initialize(mParms.mMaxSamples);

   // Set the history value array to zero and the time array to linearly
   // increasing.
   double tTimeSum=0.0;
   aHistory.startWrite();
   for (int k = 0; k < mParms.mMaxSamples; k++)
   {
      aHistory.writeSample(tTimeSum,0.0);
      tTimeSum += mParms.mTs;
   }
   aHistory.finishWrite();
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Normalize the signal history to have the desired expectation and
// uncertainty.

void HistoryGenBase::normalizeHistory(History& aHistory)
{
   //---------------------------------------------------------------------------
   // Collect statistics for the value array.

   TrialStatistics  tTrialStatistics;
   tTrialStatistics.startTrial();

   for (int k = 0; k < aHistory.mMaxSamples; k++)
   {
      tTrialStatistics.put(aHistory.mValue[k]);
   }

   tTrialStatistics.finishTrial();

   //---------------------------------------------------------------------------
   // Use the statistics to normalize the value array to get the desired
   // expectation and uncertainty.

   double tScale = 1.0;
   double tEX = tTrialStatistics.mEX;
   double tUX = tTrialStatistics.mUX;

   if (tUX != 0.0) tScale = mParms.mUX/tUX;

   for (int k = 0; k < aHistory.mMaxSamples; k++)
   {
      aHistory.mValue[k] = tScale*(aHistory.mValue[k] - tEX) + mParms.mEX;
   }
}

}//namespace