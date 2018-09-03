/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

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

HistoryGaussNoise::HistoryGaussNoise(double aSigma)
{
   initialize(aSigma);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize gaussian noise.

void HistoryGaussNoise::initialize(double aSigma)
{
   // Store variable.
   mNoiseSigma = aSigma;
   // Set flag.
   mNoiseFlag = mNoiseSigma != 0.0;

   // Seed generator.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());
#if 0
   // Set distribution parameters.
   std::normal_distribution<double>::param_type parm;
   if (mNoiseFlag) parm._Init(0.0, mNoiseSigma);
   else            parm._Init(0.0, 1.0);
   mRandomDistribution.param(parm);
#endif

   if (mNoiseFlag) mRandomDistribution = std::normal_distribution<double>(0.0, mNoiseSigma);
   else            mRandomDistribution = std::normal_distribution<double>(0.0, 1.0);
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

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace