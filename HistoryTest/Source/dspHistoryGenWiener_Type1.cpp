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
#include "dspHistoryGenWiener.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryGenWiener::HistoryGenWiener()
{
   reset();
}

HistoryGenWiener::HistoryGenWiener(HistoryGenParms& aParms)
{
   reset();
   mParms = aParms;
}

void HistoryGenWiener::reset()
{
   BaseClass::reset();
   mParms.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryGenWiener::show()
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

void HistoryGenWiener::generateHistoryType1(History& aHistory)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Initialize base class variables according to the parameters and 
   // initialize the history for the correct sample size with a zero value
   // array and a lineary increasing time array.
   BaseClass::reset();
   BaseClass::mDuration   = mParms.mDuration;
   BaseClass::mFs         = mParms.mFs;
   BaseClass::mEX         = mParms.mEX;
   BaseClass::mUX         = mParms.mUX;
   BaseClass::mNoiseSigma = 1.0;
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

   for (int k = 0; k < mNumSamples; k++)
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