/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "prnPrint.h"
#include "my_functions.h"
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
   if (!isValid()) return false;

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

void History::subtractDeltaTime(double aDeltaTime)
{
   // Add time delta to all time member variables.
   mBeginTime -= aDeltaTime;
   mEndTime   -= aDeltaTime;
   mReadTime  -= aDeltaTime;

   // Add time delta to all times in the history.
   for (int k = 0; k < mMaxSamples; k++)
   {
      mTime[k] -= aDeltaTime;
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
      // Read the time and value from the source.
      double tTime  = this->mTime[k];
      double tValue = this->mValue[k];;
      // Write the sample to the destination.
      aY.writeSample(tTime,tValue);
   }
   aY.finishWrite();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Clone this history into a new one that has the same size and time array
// and value array. This is a deep copy. This is undersampled according to
// a modulo. For example, if the modulo is two then it clones into a buffer
// that has half the number of samples and has every other time and value.

void History::createUnderSampledClone(History& aY,int aModulo)
{
   // Calculate undersampled destination max samples.
   int tMaxSamples = this->mMaxSamples/aModulo;

   // Initialize the destination to be the undersampled size.
   aY.initialize(tMaxSamples);

   // Copy the samples from the source to the destination.
   this->startRead();
   aY.startWrite();
   for (int k = 0; k < tMaxSamples; k++)
   {
      // Read the sample time and value from the source.
      double tTime  = this->mTime[k*aModulo];
      double tValue = this->mValue[k*aModulo];
      // Write the sample to the destination.
      aY.writeSample(tTime,tValue);
   }
   aY.finishWrite();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace