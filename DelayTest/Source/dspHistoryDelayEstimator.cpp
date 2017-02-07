/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dspHistoryLoopClock.h"
#include "dspHistoryDelayEstimator.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryDelayEstimator::HistoryDelayEstimator()
{
   reset();
}

void HistoryDelayEstimator::reset()
{
   mHistory1 = 0;
   mHistory2 = 0;
   mSearchFs = 0.0;
   mDelayEstimate = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Perform the search.

double HistoryDelayEstimator::search(
      History* aHistory1,
      History* aHistory2,
      double   aSearchFs,
      double   aSearchDelay,
      double   aSearchTolerance,
      int      aSearchMaxIterations)
{
   // Store these. They will be used by the error function.
   mHistory1 = aHistory1;
   mHistory2 = aHistory2;
   mSearchFs = aSearchFs;

   // Search for the delay that gives the minimum error.
   mDelayEstimate = BaseClass::search(
     -aSearchDelay,
      aSearchDelay,
      aSearchTolerance,
      aSearchMaxIterations);

   return mDelayEstimate;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Error function.

double HistoryDelayEstimator::function(double aX)
{
#if 0
   // Loop clock.
   HistoryLoopClock tClock(
      gParms.mHistoryGenParms.mDuration,
      gParms.mHistoryGenParms.mFs);

   // Start read.
   tHistory1.startRead();
   tHistory2.startRead();

   // Loop through all of the samples in the history.
   do
   {
      int    tIndex = tClock.mCount;
      double tTime  = tClock.mTime;
      double tValue1 = 0.0;
      double tValue2 = 0.0;

      // Get a sample from the history.
      tValue1 = tHistory1.readValueAtTime(tTime);
      tValue2 = tHistory2.readValueAtTime(tTime);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tIndex,
         tTime,
         tValue1,
         tValue2);
   } while (tClock.advance());
#endif
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
