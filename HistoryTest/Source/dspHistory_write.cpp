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
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

History::History()
{
   mValue = 0;
   mTime = 0;
   mMemoryFlag=false;
}

void History::resetVariables()
{
   mBeginIndex = 0;
   mEndIndex = 0;
   mBeginTime = 0.0;
   mEndTime = 0.0;
   mReadIndex = 0;
   mReadTime = 0.0;
   mWriteIndex = 0;
   mNumSamples = 0;
}

History::~History()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void History::initialize(int aMaxSamples)
{
   // If memory has already been allocated then deallocate it.
   finalize();

   // Reset member variables to defaults.
   resetVariables();

   // Initialize member variables.
   mMaxSamples = aMaxSamples;

   // Allocate memory.
   mValue = new double[aMaxSamples];
   mTime = new double[aMaxSamples];
   mMemoryFlag = true;
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void History::finalize()
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

void History::show()
{
   printf("mMaxSamples         %10d\n",  mMaxSamples);
   printf("mNumSamples         %10d\n",  mNumSamples);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Start recording a signal history. This resets member variables.

void History::startWrite()
{
   resetVariables();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finish recording a signal history.

void History::finishWrite()
{
}
      
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a sample to the signal history.

void History::writeSample(double aTime,double aValue)
{
   // Guard.
   if (!mMemoryFlag) return;

   // Guard.
   if (mNumSamples==mMaxSamples) return;

   // Store sample value and time.
   mTime [mWriteIndex] = aTime;
   mValue[mWriteIndex] = aValue;

   // If this is the first sample then store the beginning time.
   if (mWriteIndex == 0)
   {
      mBeginIndex = 0;
      mBeginTime = aTime;
   }

   // Store the ending index and time as the last that was written.
   mEndIndex = mWriteIndex;
   mEndTime = aTime;

   // Increment the index.
   mWriteIndex++;
   mNumSamples = mWriteIndex;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read a sample at a particular index.

bool History::readTimeAtIndex(int aIndex,double* aTime)
{
   // Guard.
   if (aIndex < 0) return false;
   if (aIndex >= mMaxSamples) return false;

   // Copy from array.
   *aTime = mTime[aIndex];
   // Done.
   return true;
}

bool History::readValueAtIndex(int aIndex,double* aValue)
{
   // Guard.
   if (aIndex < 0) return false;
   if (aIndex >= mMaxSamples) return false;

   // Copy from array.
   *aValue = mValue[aIndex];
   // Done.
   return true;
}

bool History::readSampleAtIndex(int aIndex, double* aTime, double* aValue)
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
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Add a time delta to all times in the history and to all time member
// variables.

void History::addDeltaTime(double aDeltaTime)
{
   // Add time delta to all time member variables.
   mBeginTime += aDeltaTime;
   mEndTime   += aDeltaTime;
   mReadTime  += aDeltaTime;

   // Add time delta to all times in the history.
   for (int k = 0; k < mMaxSamples; k++)
   {
      mTime[k] += aDeltaTime;
   }
}

}//namespace