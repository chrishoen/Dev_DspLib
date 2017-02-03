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
#include "dsp_functions.h"
#include "dspHistoryFilterCDiffBase.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryFilterCDiffBase::HistoryFilterCDiffBase()
{
   mC = 0;
   mMemoryFlag=false;
}

HistoryFilterCDiffBase::~HistoryFilterCDiffBase()
{
   finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void HistoryFilterCDiffBase::initialize(HistoryFilterParms& aParms)
{
   // If memory has already been allocated then deallocate it.
   finalize();

   // Store.
   mParms = aParms;

   // Allocate memory.
   mC = new double[mParms.mFilterOrder];
   mMemoryFlag = true;
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void HistoryFilterCDiffBase::finalize()
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

void HistoryFilterCDiffBase::show()
{
   mParms.show("Parms");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create the destination history as clone of the source history that has
// the same size and time array, but has a zero value array.

void HistoryFilterCDiffBase::createTimeClone(History& aX, History& aY)
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

}//namespace;