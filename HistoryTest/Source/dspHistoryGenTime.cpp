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
#include "dspStatistics.h"
#include "dspHistoryGenTime.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryGenTime::HistoryGenTime(HistoryGenTimeParms& aParms)
{
   mParms = aParms;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryGenTime::show()
{
   mParms.show("GenTimeParms");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize member variables. Initialize the history memory for the correct
// number of samples. Set the history value array to zero and the time array
// to lenearly increasing.

void HistoryGenTime::initializeLinearTime(History& aHistory)
{
   // Initialize variables.
   // Initialize the history.
   aHistory.initialize(mParms.mNumSamples);

   // Set the history value array to zero and the time array to linearly
   // increasing.
   double tTimeSum=0.0;
   aHistory.startWrite();
   for (int k = 0; k < mParms.mNumSamples; k++)
   {
      aHistory.writeSample(tTimeSum,0.0);
      tTimeSum += mParms.mTs;
   }
   aHistory.finishWrite();
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize member variables. Initialize the history memory for the correct
// number of samples. Set the history value array to zero and the time array
// to lenearly increasing.

void HistoryGenTime::initializeRandomTime(History& aHistory)
{
   // Initialize the history.
   aHistory.initialize(mParms.mNumSamples);

   // Initialize random variables.
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::geometric_distribution<int> tRandomDistribution(mParms.mTm);

   // Set the history value array to zero and the time array to linearly
   // increasing.
   int kevent = tRandomDistribution(tRandomGenerator);
   for (int k = 0; k < mParms.mNumSamples; k++)
   {
      if (k >= kevent)
      {
         double tTime = k * mParms.mTs;
         aHistory.writeSample(tTime,0.0);
         kevent += tRandomDistribution(tRandomGenerator);
      }
   }
   aHistory.finishWrite();
}
   
}//namespace