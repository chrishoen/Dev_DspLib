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
// Constructor

HistoryGenWiener::HistoryGenWiener()
{
   reset();
}

void HistoryGenWiener::reset()
{
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

void HistoryGenWiener::generate(History& aHistory)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Initialize base class variables and initialize the history and
   // initialize the history time array.
   BaseClass::reset();
   BaseClass::mDuration   = mParms.mDuration;
   BaseClass::mFs         = mParms.mFs;
   BaseClass::mEX         = mParms.mEX;
   BaseClass::mUX         = mParms.mUX;
   BaseClass::mNoiseSigma = 1.0;
   BaseClass::initialize(aHistory);

   // Initialize the filter.
   mFilter.initialize(
      mParms.mFilterOrder,
      mParms.mFs,
      mParms.mFc);

   //  Add a gaussian noise signal to the filter, allow it to settle.
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
      //  Add a gaussian noise signal to the filter.
      mFilter.put(getNoise());

      // Add the filtered gaussian noise to the history value array
      aHistory.mValue[k] = mFilter.mY;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Normalize the history to get the desired expectation and uncertainty.

   normalize(aHistory);
}

}//namespace