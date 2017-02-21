/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "dsp_math.h"

#include "dspHistoryLoopClock.h"
#include "dspHistoryConverters.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Convert a history with a type2 aperiodic sampling time to a history with 
// a type1 periodic sampling history. This does the conversion using
// interpolated reads according to a given sampling frequency.

void convertHistoryFromType2ToType1(
   History& aInput,
   double   aFs,
   History& aOutput)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the output history.

   // Calculate the number of samples needed to create the output history.
   int tMaxSamples = (int)(aInput.mDuration * aFs);

   // Calculate the samppling period.
   double tTs = 1.0/aFs;

   // Initialize the output history.
   aOutput.initialize(tMaxSamples);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the input history to the output history.

   // Loop time 
   double tLoopTime = 0.0;

   // Loop through all of the samples in the history.
   for (int k = 0; k < aOutput.mMaxSamples; k++)
   {
      // Get the value from the input history at the loop time. This does an
      // interpolation.
      double tValue = aInput.readValueAtTime(tLoopTime);
      // Set the time and value of the output history to the loop time and 
      // the input value.
      aOutput.mTime[k]  = tLoopTime;
      aOutput.mValue[k] = tValue;
      // Advance the loop time by the sampling period.
      tLoopTime += tTs;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

