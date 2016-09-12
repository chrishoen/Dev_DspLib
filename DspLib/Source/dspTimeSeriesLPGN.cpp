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
#include "dspTimeSeriesLPGN.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

TimeSeriesLPGN::TimeSeriesLPGN()
{
   reset();
}

void TimeSeriesLPGN::reset()
{
   BaseClass::reset();
   mFp = 1.0;
   mTp = 1.0 / mFp;
   mAlphaOneAP1 = 1.0;
   mNoiseSigma=1.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void TimeSeriesLPGN::initialize()
{
   BaseClass::initialize();

   if (mFp != 0.0)
   {
      mTp = 1.0 / mFp;
   }
   else if (mTp != 0.0)
   {
      mFp = 1.0 / mTp;
   }

   initializeNoise();

   mAlphaOneAP1 = mTs/(mTs+mTp);
   mAlphaOne1.initialize(mAlphaOneAP1);
   mAlphaOne2.initialize(mAlphaOneAP1);
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize guassian noise

void TimeSeriesLPGN::initializeNoise()
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

double TimeSeriesLPGN::getNoise()
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
// Show

void TimeSeriesLPGN::show()
{
   BaseClass::show();
   printf("mFp          %10.4f\n",mFp);
   printf("mTp          %10.4f\n",mTp);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TimeSeriesLPGN::generate()
{
   //---------------------------------------------------------------------------
   // Initialize

   initialize();

   //---------------------------------------------------------------------------
   // Generate low pass filtered guassian noise.
   // The low pass filter is two cascaded first order alpha filters.

   for (int k = 0; k < mNumSamples; k++)
   {
      // Get noise.
      double tX = getNoise();

      // Low pass filter the noise.
      mAlphaOne1.put(tX);
      mAlphaOne2.put(mAlphaOne1.mXX);
      mX[k] = mAlphaOne2.mXX;
   }

   //---------------------------------------------------------------------------
   // Normalize to get the desired expectation and uncertainty.

   normalize();
}

}//namespace