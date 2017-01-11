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

void SignalHistory::initialize(int aMaxNumSamples)
{
   // If memory has already been allocated then deallocate it.
   finalize();

   // Initialize member variables.
   mMaxNumSamples = aMaxNumSamples;
   mNumSamples = 0;
   mMeanDeltaTime = 0.0;
   mSumDeltaTime = 0.0;

   // Allocate memory.
   mValue = new double[aMaxNumSamples];
   mTime = new double[aMaxNumSamples];
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
   printf("mMaxNumSamples   %10d\n",  mMaxNumSamples);
   printf("mNumSamples      %10d\n",  mNumSamples);
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
   mK = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finish recording a signal history.

void SignalHistory::finishHistory()
{
   // Guard.
   if (mK==0)return;

   // Calculate the mean delta time.
   mMeanDeltaTime = mSumDeltaTime/double(mK);
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
   mTime[mK] = aTime;
   mValue[mK] = aValue;

   // Accumulate the delta time. Add the current delta time (the difference
   // between the current time and the previous time) to the sum.
   if (mK > 0)
   {
      mSumDeltaTime += aTime - mTime[mK - 1];
   }

   // Increment.
   mK++;
   mNumSamples = mK;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a sample at a particular index.

bool SignalHistory::getTimeAtIndex(int aIndex,double* aTime)
{
   // Guard.
   if (aIndex < 0) return false;
   if (aIndex >= mMaxNumSamples) return false;
   // Copy from array.
   *aTime = mTime[aIndex];
   // Done.
   return true;
}

bool SignalHistory::getValueAtIndex(int aIndex,double* aValue)
{
   // Guard.
   if (aIndex < 0) return false;
   if (aIndex >= mMaxNumSamples) return false;
   // Copy from array.
   *aValue = mValue[aIndex];
   // Done.
   return true;
}

bool SignalHistory::getSampleAtIndex(int aIndex, double* aTime, double* aValue)
{
   // Guard.
   if (aIndex < 0) return false;
   if (aIndex >= mMaxNumSamples) return false;
   // Copy from array.
   *aTime  = mTime[aIndex];
   *aValue = mValue[aIndex];
   // Done.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get a sample value that is closest to a particular time.

bool SignalHistory::getValueAtTime(double aTime,double* aValue)
{

}

}//namespace