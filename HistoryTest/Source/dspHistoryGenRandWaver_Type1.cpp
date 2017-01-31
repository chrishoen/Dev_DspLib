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
#include "dspHistoryGenRandWave.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryGenRandWave::HistoryGenRandWave(HistoryGenParms& aParms)
{
   mParms = aParms;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryGenRandWave::show()
{
   BaseClass::show();
   mParms.show("PARMS");
   mFilter.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the signal history according to the parameters.

void HistoryGenRandWave::generateHistoryType1(History& aHistory)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Initialize base class variables according to the parameters and 
   // initialize the history for the correct sample size with a zero value
   // array and a lineary increasing time array.
   BaseClass::initializeHistory(aHistory);

   // Initialize the filter according to the parameters.
   mFilter.initialize(
      mParms.mFilterOrder,
      mParms.mFs,
      mParms.mFc);

   //  Add some gaussian noise to the filter, allow it to settle.
   for (int k = 0; k < 1000; k++)
   {
      mFilter.put(getNoise());
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate filtered gaussian noise and add it to the history value array.

   for (int k = 0; k < mParms.mMaxSamples; k++)
   {
      //  Add gaussian noise to the filter.
      mFilter.put(getNoise());

      // Add the filtered gaussian noise to the history value array. The time
      // array has already been set.
      aHistory.mValue[k] = mFilter.mY;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Normalize the history to get the desired expectation and uncertainty.

   BaseClass::normalizeHistory(aHistory);
}

}//namespace