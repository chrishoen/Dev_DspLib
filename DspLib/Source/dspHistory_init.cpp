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

void History::reset()
{
   finalize();
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

void History::show1(int aPF,char* aLabel)
{
   Prn::print(aPF," ");
   Prn::print(aPF,"History               %10s",    aLabel);
   Prn::print(aPF,"Valid                 %10s",    my_string_from_bool(isValid()));
   Prn::print(aPF,"ResourceCount         %10d",    getResourceCount());
   Prn::print(aPF,"MaxSamples            %10d",    mMaxSamples);
   Prn::print(aPF,"NumSamples            %10d",    mNumSamples);
   Prn::print(aPF,"BeginTime             %10.4f",  mBeginTime);
   Prn::print(aPF,"EndTime               %10.4f",  mEndTime);
   Prn::print(aPF,"Duration              %10.4f",  mDuration);
}

void History::show2(int aPF,char* aLabel)
{
   Prn::print(aPF," ");
   Prn::print(aPF,"History               %10s",    aLabel);
   Prn::print(aPF,"MaxSamples            %10d",    mMaxSamples);
   Prn::print(aPF,"NumSamples            %10d",    mNumSamples);
   Prn::print(aPF,"BeginTime             %10.4f",  mBeginTime);
   Prn::print(aPF,"EndTime               %10.4f",  mEndTime);
   Prn::print(aPF,"Duration              %10.4f",  mDuration);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace