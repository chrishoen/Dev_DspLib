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
// Constructor

HistoryOperBase::HistoryOperBase()
{
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