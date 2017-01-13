/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dspHistoryGenBaseGN.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryGenBaseGN::HistoryGenBaseGN()
{
   reset();
}

void HistoryGenBaseGN::reset()
{
   BaseClass::reset();
   mNoiseSigma=1.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void HistoryGenBaseGN::initialize(History& aHistory)
{
   BaseClass::initialize(aHistory);

   initializeNoise();
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize guassian noise

void HistoryGenBaseGN::initializeNoise()
{
   // Set flag.
   mNoiseFlag = mNoiseSigma != 0.0;

   // Seed generator.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());

   // Set distribution parameters.
   std::normal_distribution<double>::param_type parm;
   if (mNoiseFlag) parm._Init(0.0, mNoiseSigma);
   else            parm._Init(0.0, 1.0);

   mRandomDistribution.param(parm);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get guassian noise

double HistoryGenBaseGN::getNoise()
{
   double tNoise;
   if (mNoiseFlag)
   {
      tNoise = mRandomDistribution(mRandomGenerator);
   }
   else
   {
      tNoise = 0.0;
   }
   return tNoise;
}
}//namespace