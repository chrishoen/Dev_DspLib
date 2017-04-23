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
// Memory control. An instance of this is allocated on the heap when 
// data memory is allocated. It contains a resource count. It used so that
// separate instances of history can point to the same allocated data memory.

class HistoryMemoryControl
{
public:

   // Resource count.
   int mResourceCount;
   // Constructor.
   HistoryMemoryControl()
   {
      mResourceCount = 0;
   }
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

History::History()
{
   Prn::print(Prn::DspRun4,"$$$$$ History constructor");
   mValue = 0;
   mTime = 0;
   mMemoryControl = 0;
   resetVariables();
   mMaxSamples = 0;
   mMaxDuration = 0.0;
}

void History::resetVariables()
{
   mNumSamples = 0;
   mWriteEnable = true;
   mWriteIndex = 0;
   mBeginIndex = 0;
   mEndIndex = 0;
   mBeginTime = 0.0;
   mEndTime = 0.0;
   mDuration = 0.0;
   mReadIndex = 0;
   mReadTime = 0.0;
}

void copyVariables(History* aY, const History* aX)
{
   aY->mValue         = aX->mValue;
   aY->mTime          = aX->mTime;
   aY->mMemoryControl = aX->mMemoryControl;

   aY->mMaxSamples    = aX->mMaxSamples;
   aY->mMaxDuration   = aX->mMaxDuration;

   aY->mNumSamples    = aX->mNumSamples;
   aY->mWriteEnable   = aX->mWriteEnable;
   aY->mWriteIndex    = aX->mWriteIndex;
   aY->mBeginIndex    = aX->mBeginIndex;
   aY->mEndIndex      = aX->mEndIndex;
   aY->mBeginTime     = aX->mBeginTime;
   aY->mEndTime       = aX->mEndTime;
   aY->mDuration      = aX->mDuration;
   aY->mReadIndex     = aX->mReadIndex;
   aY->mReadTime      = aX->mReadTime;
}

History::~History()
{
   Prn::print(Prn::DspRun4,"$$$$$ History destructor");
   // If memory has already been allocated then deallocate it.
   decrementResourceCount();
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
   mMemoryControl = new HistoryMemoryControl;

   incrementResourceCount();
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void History::finalize()
{
   // If memory was allocated then deallocate it.
   if (mMemoryControl)
   {
      delete mValue;
      delete mTime;
      delete mMemoryControl;
      mValue = 0;
      mTime = 0;
      mMemoryControl=0;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Resource count management.

void History::incrementResourceCount()
{
   // Guard.
   if (mMemoryControl==0) return;
   // Increment the resource count.
   mMemoryControl->mResourceCount++;
}

void History::decrementResourceCount()
{
   // Guard.
   if (mMemoryControl==0) return;
   // If there is no memory allocated then return.
   if (mMemoryControl->mResourceCount==0) return;

   // Decrement the resource count. If it is zero then deallocate memory.
   if (--mMemoryControl->mResourceCount == 0)
   {
      finalize();
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Memory status.

// Return true if memory has been allocated.
bool History::isValid()
{
   return mMemoryControl!=0;
}

// Return resource count. If memory has not been allocated return -1.
int  History::getResourceCount()
{
   if (mMemoryControl==0) return -1;
   return mMemoryControl->mResourceCount;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Copy constructor and assignment operator. Copy variables and data
// pointers. Do not copy data. This makes a copy of a history variable 
// that points to the same allocated memory

History::History(const History& aRhs)
{
   Prn::print(Prn::DspRun4,"$$$$$ History copy constructor");
   copyVariables(this,&aRhs);
   incrementResourceCount();
}

History& History::operator= (const History& aRhs)
{
   Prn::print(Prn::DspRun4,"$$$$$ History assignment");

   if(this == &aRhs) return *this;
   copyVariables(this,&aRhs);
   incrementResourceCount();
   return *this;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void History::show(char* aLabel)
{
   if (aLabel)
   {
   Prn::print(Prn::DspRun1,"History             %10s",  aLabel);
   }

   Prn::print(Prn::DspRun1,"Valid               %10s",  my_string_from_bool(isValid()));
   Prn::print(Prn::DspRun1,"ResourceCount       %10d",  getResourceCount());
   Prn::print(Prn::DspRun1,"mMaxSamples         %10d",  mMaxSamples);
   Prn::print(Prn::DspRun1,"mNumSamples         %10d",  mNumSamples);

   if (aLabel)
   {
   Prn::print(Prn::DspRun1,"");
   }
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
      // Read the time from the source.
      double tTime  = this->mTime[k];
      double tValue = this->mValue[k];;
      // Write the sample to the destination, same time, zero value.
      aY.writeSample(tTime,tValue);
   }
   aY.finishWrite();
}

}//namespace