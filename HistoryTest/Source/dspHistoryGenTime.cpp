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

HistoryGenTime::HistoryGenTime(HistoryGenParms& aParms)
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
// Initialize the history memory for the correct number of samples. Set the
// history value array to zero and the time array to linearly increasing. This 
// has constant intersample arrival times.

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
// Initialize the history memory for the correct number of samples. Set the
// history value array to zero and the time array to linearly increasing. This
// has random intersample arrival times, based on an exponential random
// distribution.

void HistoryGenTime::initializeRandomTime(History& aHistory)
{
   mParms.show("GenTime");
   // Initialize the history.
   aHistory.initialize(mParms.mNumSamples);

   // Initialize random variables.
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::exponential_distribution<double> tRandomDistribution(mParms.mFs);

   // Set the history value array to zero and the time array to linearly
   // increasing.
   double tTime = 0.0;
   for (int k = 0; k < mParms.mNumSamples; k++)
   {     double tDeltaTime = tRandomDistribution(tRandomGenerator);
         tTime += tDeltaTime;
         aHistory.writeSample(tTime,0.0);
   }
   aHistory.finishWrite();
}
   
}//namespace