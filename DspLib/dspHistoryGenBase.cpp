/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dsp_math.h"
#include "dspTrialStatistics.h"
#include "dspHistoryGaussNoise.h"
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
// Initialize member variables. Allocate the history memory for the correct
// number of samples, according to the parameters. Set the history value array
// to zero and the time array to linearly increasing.
// Type1 is  periodic, with   regular intersample arrival times.
// Type2 is aperiodic, with irregular intersample arrival times.

void HistoryGenBase::initializeHistoryType1(History& aHistory)
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
// Initialize member variables. Allocate the history memory for the correct
// number of samples, according to the parameters. Set the history value array
// to zero and the time array to linearly increasing.
// Type1 is  periodic, with   regular intersample arrival times.
// Type2 is aperiodic, with irregular intersample arrival times.

void HistoryGenBase::initializeHistoryType2(History& aHistory)
{
   // Initialize the history.
   aHistory.initialize(mParms.mMaxSamples);

   // Initialize random variables.
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::exponential_distribution<double> tRandomDistribution(mParms.mFs);

   // Set the history value array to zero and the time array to linearly
   // increasing with a random intersample arrival time.
   double tTime = 0.0;
   for (int k = 0; k < mParms.mMaxSamples; k++)
   {     double tDeltaTime = tRandomDistribution(tRandomGenerator);
         tTime += tDeltaTime;
         aHistory.writeSample(tTime,0.0);
   }
   aHistory.finishWrite();
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Based on the parms, this calls one of the above, Type1 or Type2.

void HistoryGenBase::generateHistory(History& aHistory)
{
   switch (mParms.mTimeType)
   {
   case HistoryGenParms::cTimeType1 : 
      generateHistoryType1(aHistory);
      break;
   case HistoryGenParms::cTimeType2 : 
      generateHistoryType2(aHistory);
      break;
   }
   
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Add gaussian noise to the history sample values.

void HistoryGenBase::addNoise(History& aHistory)
{
   HistoryGaussNoise tNoise(mParms.mSigma);

   for (int k = 0; k < aHistory.mMaxSamples; k++)
   {
      aHistory.mValue[k] += tNoise.getNoise();
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Normalize the signal history to have the desired expectation and
// uncertainty.

void HistoryGenBase::normalizeHistory(History& aHistory)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics for the value array.

   TrialStatistics  tTrialStatistics;
   tTrialStatistics.startTrial();

   for (int k = 0; k < aHistory.mMaxSamples; k++)
   {
      tTrialStatistics.put(aHistory.mValue[k]);
   }

   tTrialStatistics.finishTrial();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
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

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace