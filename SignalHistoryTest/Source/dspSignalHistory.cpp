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
   mX = 0;
   mT = 0;
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
   mMeanDeltaT = 0.0;
   mSumDeltaT = 0.0;

   // Allocate memory.
   mX = new double[aMaxNumSamples];
   mT = new double[aMaxNumSamples];
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
      delete mX;
      delete mT;
      mX = 0;
      mT = 0;
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
   printf("mMeanDeltaT      %10.4f\n",mMeanDeltaT);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Start recording a signal history. This resets member variables.

void SignalHistory::startHistory()
{
   mMeanDeltaT = 0.0;
   mSumDeltaT = 0.0;
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
   mMeanDeltaT = mSumDeltaT/double(mK);
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
   mT[mK] = aTime;
   mX[mK] = aValue;

   // Accumulate the delta time. Add the current delta time (the difference
   // between the current time and the previous time) to the sum.
   if (mK > 0)
   {
      mSumDeltaT += aTime - mT[mK - 1];
   }

   // Increment.
   mK++;
}

}//namespace