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
// Collect trial statistics on the value array of a signal history.

void HistoryStatistics::collectValue(History& aHistory)
{
   // Start the statistics.
   BaseClass::startTrial();

   // Loop through all of the samples in the history.
   for (int k = 0; k < aHistory.mNumSamples; k++)
   {
      // Put history value to statistics.
      BaseClass::put(aHistory.mValue[k]);
   }

   // Finish the statistics.
   BaseClass::finishTrial();
}

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

}//namespace