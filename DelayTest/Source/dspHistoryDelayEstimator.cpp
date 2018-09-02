/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

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
// Perform the search. Find the delay that minimizes the error function.

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
// f(x). Error function. x is the variable delay.
// Return the sum of the square of the difference between the two
// histories, one is evaluated at time t and the other is evaluated at
// time t + delay.

double HistoryDelayEstimator::function(double aX)
{
   // Loop clock.
   HistoryLoopClock tClock(
      mHistory1->mBeginTime,
      mHistory1->mEndTime,
      mSearchFs);

   // Start read.
   mHistory1->startRead();
   mHistory2->startRead();

   // Loop variables.
   double tErrorSqSum = 0.0;

   // Loop through all of the samples in the history.
   do
   {
      double tTime  = tClock.mTime;
      double tValue1 = 0.0;
      double tValue2 = 0.0;

      // Get a sample from the history.
      tValue1 = mHistory1->readValueAtTime(tTime);
      tValue2 = mHistory2->readValueAtTime(tTime + aX);

      // Calculate square of error and add it to the sum.
      double tError = tValue2 - tValue1;
      double tErrorSq = tError*tError;
      tErrorSqSum += tErrorSq;

   } while (tClock.advance());

   // Return the error squared.
   return tErrorSqSum;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
