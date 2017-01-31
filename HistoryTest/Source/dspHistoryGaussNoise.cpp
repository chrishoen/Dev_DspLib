/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dspHistoryGaussNoise.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

HistoryGaussNoise::HistoryGaussNoise()
{
   mNoiseSigma=0.0;
   mNoiseSigma=false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize gaussian noise.

void HistoryGaussNoise::initializeNoise()
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
// Get gaussian noise.

double HistoryGaussNoise::getNoise()
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