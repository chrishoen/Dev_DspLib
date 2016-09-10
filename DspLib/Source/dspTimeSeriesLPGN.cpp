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

TimeSeriesLPGN::~TimeSeriesLPGN()
{
   if (mX) delete mX;
}

void TimeSeriesLPGN::reset()
{
   mX=0;
   mFs = 1.0;
   mTs = 1.0 / mFs;
   mFp = 1.0;
   mTp = 1.0 / mFp;

   mDuration = 10.0;
   mNumSamples = (int)(mDuration * mFs);

   mEX = 0.0;
   mUX = 1.0;

   mAlphaOneAP1 = 1.0;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void TimeSeriesLPGN::initialize()
{
   if (mFs != 0.0)
   {
      mTs = 1.0 / mFs;
   }
   else if (mTs != 0.0)
   {
      mFs = 1.0 / mTs;
   }

   if (mFp != 0.0)
   {
      mTp = 1.0 / mFp;
   }
   else if (mTp != 0.0)
   {
      mFp = 1.0 / mTp;
   }

   mSigmaFlag = false;
   initializeNoise();

   mAlphaOneAP1 = mTs/(mTs+mTp);
   mAlphaOne1.initialize(mAlphaOneAP1);
   mAlphaOne2.initialize(mAlphaOneAP1);

   mNumSamples = (int)(mDuration * mFs);
   mX = new double[mNumSamples];
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Guassian noise

// Initialize random distribution.
void TimeSeriesLPGN::initializeNoise()
{
   mNoiseSigma=1.0;
   // Set flag.
   mSigmaFlag = mNoiseSigma != 0.0;

   // Seed generator.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());

   // Set distribution parameters.
   std::normal_distribution<double>::param_type parm;
   if (mSigmaFlag) parm._Init(0.0, mNoiseSigma);
   else            parm._Init(0.0, 1.0);

   mRandomDistribution.param(parm);
}

// Get noise from random distribution.
double TimeSeriesLPGN::getNoise()
{
   double tNoise;
   if (mSigmaFlag)
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
   printf("mDuration    %10.4f\n",mDuration);
   printf("mNumSamples  %10d\n",  mNumSamples);
   printf("mFs          %10.4f\n",mFs);
   printf("mTs          %10.4f\n",mTs);
   printf("mFp          %10.4f\n",mFp);
   printf("mTp          %10.4f\n",mTp);
   printf("mEX          %10.4f\n",mEX);
   printf("mUX          %10.4f\n",mUX);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TimeSeriesLPGN::generate()
{
   //---------------------------------------------------------------------------
   // Initialize

   initialize();
   initializeNoise();

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
   // Statistics.

   TrialStatistics  tTrialStatistics;
   tTrialStatistics.startTrial();

   for (int k = 0; k < mNumSamples; k++)
   {
      tTrialStatistics.put(mX[k]);
   }

   tTrialStatistics.finishTrial();

   //---------------------------------------------------------------------------
   // Normalize to get the desired expectation and uncertainty.

   double tScale = 1.0;
   double tEX = tTrialStatistics.mEX;
   double tUX = tTrialStatistics.mUX;

   if (tUX != 0.0) tScale = mUX/tUX;

   for (int k = 0; k < mNumSamples; k++)
   {
      mX[k] = tScale*(mX[k] - tEX) + mEX;
   }
}

}//namespace