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
#include "dspHistoryGenRandWave.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the signal history according to the parameters.

void HistoryGenRandWave::generateHistoryType2(History& aHistory)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the history with Type2 sample timing. Random intersample
   // arrival times, zero values.

   BaseClass::initializeHistoryType2(aHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a temp history with Type1 sampling time and a random wave.
   // Periodic intersample arrival times, random wave values.

   // Signal history.
   History tHistory2;

   // Signal history generator.
   HistoryGenRandWave tGen2(mParms);

   // Generate the history.
   tGen2.generateHistoryType1(tHistory2);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the two temp signal history to the output signal
   // history.

   // Loop through all of the samples in the history.
   for (int k = 0; k < aHistory.mMaxSamples; k++)
   {
      // Get the time from the first history.
      double tTime  = aHistory.mTime[k];
      // Get the value from the second history at that time.
      double tValue = tHistory2.readValueAtTime(tTime);
      // Set the value from the first history to the concurrent value
      // of the second history.
      aHistory.mValue[k] = tValue;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Normalize the history to get the desired expectation and uncertainty.

   BaseClass::normalizeHistory(aHistory);
}

}//namespace