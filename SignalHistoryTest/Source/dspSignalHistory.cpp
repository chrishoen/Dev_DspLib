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
#include "dspSignalHistory.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

SignalHistory::SignalHistory()
{
   mValue = 0;
   mTime = 0;
   mMemoryFlag=false;
}

SignalHistory::~SignalHistory()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void SignalHistory::initialize(int aMaxSamples)
{
   // If memory has already been allocated then deallocate it.
   finalize();

   // Initialize member variables.
   mMaxSamples = aMaxSamples;
   mNumSamples = 0;
   mMeanDeltaTime = 0.0;
   mSumDeltaTime = 0.0;

   // Allocate memory.
   mValue = new double[aMaxSamples];
   mTime = new double[aMaxSamples];
   mMemoryFlag = true;
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void SignalHistory::finalize()
{
   // If memory was allocated then deallocate it.
   if (mMemoryFlag)
   {
      delete mValue;
      delete mTime;
      mValue = 0;
      mTime = 0;
      mMemoryFlag=false;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void SignalHistory::show()
{
   printf("mMaxSamples         %10d\n",  mMaxSamples);
   printf("mNumSamples         %10d\n",  mNumSamples);
   printf("mMeanDeltaTime      %10.4f\n",mMeanDeltaTime);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Start recording a signal history. This resets member variables.

void SignalHistory::startHistory()
{
   mMeanDeltaTime = 0.0;
   mSumDeltaTime = 0.0;
   mNumSamples = 0;
   mIndex = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finish recording a signal history.

void SignalHistory::finishHistory()
{
   // Guard.
   if (mIndex==0)return;

   // Calculate the mean delta time.
   mMeanDeltaTime = mSumDeltaTime/double(mIndex);
}
      
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a sample to the signal history.

void SignalHistory::putSample(double aTime,double aValue)
{
   // Guard.
   if (!mMemoryFlag) return;

   // Store sample value and time.
   mTime[mIndex] = aTime;
   mValue[mIndex] = aValue;

   // Accumulate the delta time. Add the current delta time (the difference
   // between the current time and the previous time) to the sum.
   if (mIndex > 0)
   {
      mSumDeltaTime += aTime - mTime[mIndex - 1];
   }

   // Increment.
   mIndex++;
   mNumSamples = mIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a sample at a particular index.

bool SignalHistory::getTimeAtIndex(int aIndex,double* aTime)
{
   // Guard.
   if (aIndex < 0) return false;
   if (aIndex >= mMaxSamples) return false;
   // Copy from array.
   *aTime = mTime[aIndex];
   // Done.
   return true;
}

bool SignalHistory::getValueAtIndex(int aIndex,double* aValue)
{
   // Guard.
   if (aIndex < 0) return false;
   if (aIndex >= mMaxSamples) return false;
   // Copy from array.
   *aValue = mValue[aIndex];
   // Done.
   return true;
}

bool SignalHistory::getSampleAtIndex(int aIndex, double* aTime, double* aValue)
{
   // Guard.
   if (aIndex < 0) return false;
   if (aIndex >= mMaxSamples) return false;
   // Copy from array.
   *aTime  = mTime[aIndex];
   *aValue = mValue[aIndex];
   // Done.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a sample value that is interpolated from a target time that is
// calculated to be the time at an input index minus an input delta.
// If the target time is not between the time at the input index and
// the time of the previous index then a downward search is performed 
// until it is found.

bool SignalHistory::getValueInterpolateBefore (
   int     aIndex, 
   double  aBeforeDeltaTime,
   double* aValue)
{
   // Calculate the target time to interpolate to. This is the time of the
   // input index minus a delta. The target time is before the upper limit.
   double tTargetTime = mTime [aIndex] - aBeforeDeltaTime;

   // Initialize the index to start the search at.
   int tIndex = aIndex;

   // Loop until the time to interpolate is found. When it is, perform the 
   // interpolation.
   while (true)
   {
      // Guard.
      if (tIndex < 3) return false;
      if (tIndex >= mMaxSamples-3) return false;

      // Locals, index one is after index zero. Time one is after time zero.
      double tTime1  = mTime [tIndex];       // Time  at the input    index, upper limit.
      double tTime0  = mTime [tIndex - 1];   // Time  at the previous index, lower limit.
      double tValue1 = mValue[tIndex];       // Value at the input    index.
      double tValue0 = mValue[tIndex - 1];   // Value at the previous index.

      // Guard.
      if (tTime1 == tTime0) return false;

      // If the target time is before the lower limit then continue
      // the search (go back to the start of the loop).
      if (tTargetTime < tTime0)
      {
         // Advance the seacrh downward.
         tIndex--;
         // Goto the top of the loop.
         continue;
      }
      // At this point, the target time is within the upper and lower limits,
      // so calculate the linear interpolation of the target time between them.
      double tValue = tValue0 + (tTargetTime - tTime0)*(tValue1 - tValue0) / (tTime1 - tTime0);
      // Exit the loop.
      break;
   }

   // Done.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a sample value that is interpolated from a target time that is
// calculated to be the time at an input index plus an input delta.
// If the target time is not between the time at the input index and
// the time of the next index then a upward search is performed 
// until it is found.

bool SignalHistory::getValueInterpolateAfter (
   int     aIndex, 
   double  aAfterDeltaTime,
   double* aValue)
{
   // Calculate the target time to interpolate to. This is the time of the
   // input index plus a delta. The target time is after the lower limit.
   double tTargetTime = mTime [aIndex] + aAfterDeltaTime;

   // Initialize the index to start the search at.
   int tIndex = aIndex;

   // Loop until the time to interpolate is found. When it is, perform the 
   // interpolation.
   while (true)
   {
      // Guard.
      if (tIndex < 3) return false;
      if (tIndex >= mMaxSamples-3) return false;

      // Locals, index one is after index zero. Time one is after time zero.
      double tTime1  = mTime [tIndex + 1];    // Time  at the next     index, upper limit.
      double tTime0  = mTime [tIndex];        // Time  at the input    index, lower limit.
      double tValue1 = mValue[tIndex + 1];    // Value at the next     index.
      double tValue0 = mValue[tIndex];        // Value at the input    index.

      // Guard.
      if (tTime1 == tTime0) return false;

      // If the target time is after the upper limit then continue
      // the search (go back to the start of the loop).
      if (tTargetTime > tTime1)
      {
         // Advance the seacrh downward.
         tIndex--;
         // Goto the top of the loop.
         continue;
      }
      // At this point, the target time is within the upper and lower limits,
      // so calculate the linear interpolation of the target time between them.
      double tValue = tValue0 + (tTargetTime - tTime0)*(tValue1 - tValue0) / (tTime1 - tTime0);
      // Exit the loop.
      break;
   }

   // Done.
   return true;
}

}//namespace