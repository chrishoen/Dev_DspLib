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
#include "dspHistoryStatistics.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Collect trial statistics on the time array of a signal history.

void HistoryStatistics::collectTime(History& aHistory)
{
   // Start the statistics.
   BaseClass::startTrial();

   // Loop through all of the samples in the history.
   for (int k = 0; k < aHistory.mNumSamples; k++)
   {
      // Put history value to statistics.
      BaseClass::put(aHistory.mTime[k]);
   }

   // Finish the statistics.
   BaseClass::finishTrial();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Collect trial statistics on the value array of a signal history.

void HistoryStatistics::collectValue(History& aHistory)
{
   // Start the statistics.
   BaseClass::startTrial();


   // Add the value array to the statistics.
   addValue(aHistory);

   // Finish the statistics.
   BaseClass::finishTrial();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Collect trial statistics on the value array of a signal history.
// Exclude values that are not within a region of interest defined
// from begin time + exclusion to end time - exclusion.

void HistoryStatistics::collectValue(History& aHistory, double aTimeExclusion)
{
   // Start the statistics.
   BaseClass::startTrial();

   // Add the value array to the statistics.
   addValue(aHistory,aTimeExclusion);

   // Finish the statistics.
   BaseClass::finishTrial();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Collect trial statistics on the value array of a signal history.

void HistoryStatistics::addValue(History& aHistory)
{

   // Loop through all of the samples in the history.
   for (int k = 0; k < aHistory.mNumSamples; k++)
   {
      // Put history value to statistics.
      BaseClass::put(aHistory.mValue[k],aHistory.mTime[k]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Collect trial statistics on the value array of a signal history.
// Exclude values that are not within a region of interest defined
// from begin time + exclusion to end time - exclusion.

void HistoryStatistics::addValue(History& aHistory, double aTimeExclusion)
{
   // Loop through all of the samples in the history.
   for (int k = 0; k < aHistory.mNumSamples; k++)
   {
      // Calculate if the time is within the region of interest.
      double tBeginTime  = aHistory.mBeginTime + aTimeExclusion;
      double tEndTime    = aHistory.mEndTime   - aTimeExclusion;
      double tTime       = aHistory.mTime[k];
      bool   tGoingTime  = tTime >= tBeginTime && tTime <= tEndTime;

      // If the time is within the region of interest.
      if (tGoingTime)
      {
         // Put history value to statistics.
         BaseClass::put(aHistory.mValue[k], aHistory.mTime[k]);
      }
   }
}

}//namespace