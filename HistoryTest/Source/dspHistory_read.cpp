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
#include "dspHistory.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read values from the signal history, based on time.
// This is used in loops that process type2 signal histories. Samples are
// read from the history at monotically increasing times. The read is
// advanced through the history arrays and an interpolated value between
// array entries is returned. The reads must occur in sequential access such
// that the time of a read must be after the time of the previous read.

   void History::startRead()
{
   // Set the last read index and time at the beginning.
   mReadIndex = mBeginIndex;
   mReadTime  = mBeginTime;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read value at a specific time. This is called repeatedly in a loop where
// the read time is monotonic increasing. An interpolated value between
// array entries is returned. This allows a history to be approximated as a
// continuous function of a real time variable.

double History::readValueAtTime(double aReadTime)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Guard.

   // If the read time is before the begin time then set the last read
   // variables for the beginning and return the beginning value.
   if (aReadTime <= mBeginTime)
   {
      // Set the last read to the beginning.
      aReadTime  = mBeginTime;
      mReadIndex = mBeginIndex;
      mReadTime  = mBeginTime;
      // Return the first value.
      return mValue[mReadIndex];
   }

   // If the read time is after the end time then set the last read
   // variables for the end and return the ending value.
   if (aReadTime >= mEndTime)
   {
      // Set the last read to the beginning.
      aReadTime  = mEndTime;
      mReadIndex = mEndIndex;
      mReadTime  = mEndTime;
      // Return the first value.
      return mValue[mReadIndex];
   }

   // If the read time is before the last read time then return the last 
   // read value.
   if (aReadTime <= mReadTime)
   {
      // Return the last read value.
      return mValue[mReadIndex];
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read forward at a given time.

   // Initialize loop variables.
   int tIndex = mReadIndex;
   double tValue = 0.0;

   // Loop until the time to interpolate is found. When it is, perform the 
   // interpolation.
   while (true)
   {
      // Locals, index one is after index zero. Time one is after time zero.
      double tTime0  = mTime [tIndex];        // Time  at the last read index, lower limit.
      double tTime1  = mTime [tIndex + 1];    // Time  at the next read index, upper limit.
      double tValue0 = mValue[tIndex];        // Value at the last read index.
      double tValue1 = mValue[tIndex + 1];    // Value at the next read index.

      // Guard. Exit the loop. This shouldn't happen.
      if (tTime1 == tTime0) break;

      // If the target read time is after the upper limit then continue
      // the search (go back to the start of the loop).
      if (aReadTime > tTime1)
      {
         // Advance the search forward.
         tIndex++;
         // Goto the top of the loop.
         continue;
      }

      // At this point, the target time is within the upper and lower limits,
      // so calculate the linear interpolation of the target time between them.
      tValue = tValue0 + (aReadTime - tTime0)*(tValue1 - tValue0) / (tTime1 - tTime0);
      // Store variables.
      mReadIndex = tIndex;
      mReadTime  = aReadTime;
      // Exit the loop.
      break;
   }
   // Return the interpolated value.
   return tValue;
}

}//namespace