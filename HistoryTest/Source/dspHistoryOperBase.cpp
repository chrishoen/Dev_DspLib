/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <random>

#include "dsp_math.h"
#include "dspHistoryOperBase.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryOperBase::HistoryOperBase()
{
   mC = 0;
   mMemoryFlag=false;
}

HistoryOperBase::~HistoryOperBase()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void HistoryOperBase::initialize(HistoryOperParms& aParms)
{
   // If memory has already been allocated then deallocate it.
   finalize();

   // Store.
   mParms = aParms;

   // Allocate memory.
   int tM = mParms.mM;
   if (tM > 0)
   {
      // Allocate memory.
      mC = new double[tM * 2 + 1];
      mMemoryFlag = true;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void HistoryOperBase::finalize()
{
   // If memory was allocated then deallocate it.
   if (mMemoryFlag)
   {
      delete mC;
      mC = 0;
      mMemoryFlag=false;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryOperBase::show()
{
   mParms.show("Parms");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create a clone of the source that has the same size and time array,
// but has a zero value array.

void HistoryOperBase::createTimeClone(History& aX, History& aY)
{
   // Initialize the destination to be the same size as the source.
   aY.initialize(aX.mMaxSamples);

   // Copy the samples from the source to the destination.
   aX.startRead();
   aY.startWrite();
   for (int k = 0; k < aX.mMaxSamples; k++)
   {
      // Read the time from the source.
      double tTime  = aX.mTime[k];
      double tValue = 0.0;
      // Write the sample to the destination, same time, zero value.
      aY.writeSample(tTime,tValue);
   }
   aY.finishWrite();
}

}//namespace