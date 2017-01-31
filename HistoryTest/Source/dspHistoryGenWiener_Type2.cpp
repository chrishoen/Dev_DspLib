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
#include "dspHistoryGenTime.h"
#include "dspHistoryGenWiener.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the signal history according to the parameters.

void HistoryGenWiener::generateHistoryType2(History& aHistory)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the generator base class.

   // Initialize base class variables according to the parameters and 
   // initialize the history for the correct sample size with a zero value
   // array and a lineary increasing time array.
   BaseClass::reset();
   BaseClass::mDuration   = mParms.mDuration;
   BaseClass::mFs         = mParms.mFs;
   BaseClass::mEX         = mParms.mEX;
   BaseClass::mUX         = mParms.mUX;
   BaseClass::mNoiseSigma = 1.0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the history.

   BaseClass::initializeHistory(aHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a temp signal history. Random time. Zero value.

   // Signal history.
   History tHistory1;

   // Signal history generator.
   HistoryGenTimeParms tGenTimeParms(
      mParms.mDuration,
      mParms.mFs);

   HistoryGenTime tGen1(tGenTimeParms);

   // Generate the history.
   tGen1.initializeRandomTime(tHistory1);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a temp signal history. Periodic time. Wiener wave value.

   // Signal history.
   History tHistory2;

   // Signal history generator.
   HistoryGenWiener tGen2(mParms);

   // Generate the history.
   tGen2.generateHistoryType1(tHistory2);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the two temp signal history to the output signal
   // history.


   tHistory1.startRead();
   tHistory2.startRead();

   aHistory.startWrite();

   // Loop through all of the samples in the history.
   for (int k = 0; k < tHistory2.mNumSamples; k++)
   {
      int    tIndex = k;
      double tTime  = tHistory1.mTime[k];
      double tValue = tHistory2.readValueAtTime(tTime);

      aHistory.writeSample(tTime,tValue);
   }

   aHistory.finishWrite();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Normalize the history to get the desired expectation and uncertainty.

   BaseClass::normalizeHistory(aHistory);
}

}//namespace