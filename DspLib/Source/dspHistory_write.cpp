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
#include "dspHistoryGaussNoise.h"
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
   mDuration = 0.0;
   mReadIndex = 0;
   mReadTime = 0.0;
   mWriteIndex = 0;
   mWriteEnable = true;
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

void History::initialize(int aMaxSamples,double aMaxDuration)
{
   // If memory has already been allocated then deallocate it.
   finalize();

   // Reset member variables to defaults.
   resetVariables();

   // Initialize member variables.
   mMaxSamples = aMaxSamples;
   mMaxDuration = aMaxDuration;

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
   mWriteEnable = false;
}
      
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a sample to the signal history.

bool History::writeSample(double aTime,double aValue)
{
   // Guard.
   if (!mMemoryFlag) return false;

   // Guard.
   if (!mWriteEnable) return false;

   // Guard.
   if (mNumSamples == mMaxSamples)
   {
      mWriteEnable = false;
      return false;
   }

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
   mDuration = mEndTime - mBeginTime;

   // Increment the index.
   mWriteIndex++;
   mNumSamples = mWriteIndex;

   double tDuration = mEndTime - mBeginTime;
   if (mMaxDuration > 0.0)
   {
      if (tDuration >= mMaxDuration)
      {
         mWriteEnable = false;
         return true;
      }
   }

   // Sample was written successfully.
   return true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return true if the last write that was started is finished.

bool History::writeFinished()
{
   return !mWriteEnable; 
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

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Add gaussian noise to the values.

void History::addNoise(double aSigma)
{
   HistoryGaussNoise tNoise(aSigma);

   for (int k = 0; k < mMaxSamples; k++)
   {
      mValue[k] += tNoise.getNoise();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Clone this history into a new one that has the same size and time array,
// but has a zero value array.

void History::createTimeClone(History& aY)
{
   // Initialize the destination to be the same size as the source.
   aY.initialize(this->mMaxSamples);

   // Copy the samples from the source to the destination.
   this->startRead();
   aY.startWrite();
   for (int k = 0; k < this->mMaxSamples; k++)
   {
      // Read the time from the source.
      double tTime  = this->mTime[k];
      double tValue = 0.0;
      // Write the sample to the destination, same time, zero value.
      aY.writeSample(tTime,tValue);
   }
   aY.finishWrite();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Clone this history into a new one that has the same size and time array,
// and value array.

void History::createClone(History& aY)
{
   // Initialize the destination to be the same size as the source.
   aY.initialize(this->mMaxSamples);

   // Copy the samples from the source to the destination.
   this->startRead();
   aY.startWrite();
   for (int k = 0; k < this->mMaxSamples; k++)
   {
      // Read the time from the source.
      double tTime  = this->mTime[k];
      double tValue = this->mValue[k];;
      // Write the sample to the destination, same time, zero value.
      aY.writeSample(tTime,tValue);
   }
   aY.finishWrite();
}

}//namespace