/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dsp_math.h"
#include "dspStatistics.h"
#include "dspHistoryGenRandWave.h"

namespace Dsp
{


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
   BaseClass::initializeHistoryType1(aHistory);

   // Initialize the gaussian noise generator.
   mNoise.initialize(1.0);

   // Initialize the filter according to the parameters.
   mFilter.initialize(
      mParms.mFilterOrder,
      mParms.mFs,
      mParms.mFc);

   //  Add some gaussian noise to the filter, allow it to settle.
   for (int k = 0; k < 1000; k++)
   {
      mFilter.put(mNoise.getNoise());
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate filtered gaussian noise and add it to the history value array.

   for (int k = 0; k < mParms.mMaxSamples; k++)
   {
      //  Add gaussian noise to the filter.
      mFilter.put(mNoise.getNoise());

      // Add the filtered gaussian noise to the history value array. The time
      // array has already been set.
      aHistory.mValue[k] = mFilter.mY;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Normalize the history to get the desired expectation and uncertainty.

   BaseClass::normalizeHistory(aHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Add gaussian noise to the history sample array.

    BaseClass::addNoise(aHistory);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the signal history according to the parameters.

void HistoryGenRandWave::generateHistoryType2(History& aHistory)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the history with Type2 sample timing. Random intersample
   // arrival times, zero values.

   BaseClass::initializeHistoryType2(aHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a temp history with Type1 sampling time and a random wave.
   // Periodic intersample arrival times, random wave values.

   // Signal history.
   History tHistory2;

   // Signal history generator.
   HistoryGenRandWave tGen2(mParms);

   // Generate the history.
   tGen2.generateHistoryType1(tHistory2);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the two temp signal history to the output signal
   // history.

   // Loop through all of the samples in the history.
   for (int k = 0; k < aHistory.mMaxSamples; k++)
   {
      // Get the time from the first history.
      double tTime  = aHistory.mTime[k];
      // Get the value from the second history at that time.
      double tValue = tHistory2.readValueAtTime(tTime);
      // Set the value from the first history to the concurrent value
      // of the second history.
      aHistory.mValue[k] = tValue;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Add gaussian noise to the history sample array.

    BaseClass::addNoise(aHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Normalize the history to get the desired expectation and uncertainty.

   BaseClass::normalizeHistory(aHistory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace