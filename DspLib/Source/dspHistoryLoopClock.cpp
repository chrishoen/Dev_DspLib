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

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

HistoryLoopClock::HistoryLoopClock(double aDuration, double aFs)
{
   mDuration = aDuration;
   mFs       = aFs;

   mTime     = 0.0;
   mCount    = 0;

   mTs = 1.0 / mFs;
   mMaxCount = (int)(mDuration * mFs);
}

HistoryLoopClock::HistoryLoopClock(
      double aBeginTime, 
      double aEndTime, 
      double aFs)
{
   mDuration = aEndTime - aBeginTime;
   mFs       = aFs;

   mTime     = 0.0;
   mCount    = 0;

   mTs = 1.0 / mFs;
   mMaxCount = (int)(mDuration * mFs);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Advance forward through time, updating the time and count variables.
// Return false if the time duration has been reached. 

bool HistoryLoopClock::advance()
{
   mTime     += mTs;
   mCount    += 1;

   return mCount != mMaxCount;
}
}//namespace