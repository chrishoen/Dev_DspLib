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
#include "dspTimeSeriesHarmonic.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

TimeSeriesHarmonic::TimeSeriesHarmonic()
{
   reset();
}

TimeSeriesHarmonic::~TimeSeriesHarmonic()
{
   if (mX) delete mX;
}

void TimeSeriesHarmonic::reset()
{
   mX=0;
   mFs = 1.0;
   mTs = 1.0 / mFs;

   mDuration = 10.0;
   mNumSamples = (int)(mDuration * mFs);

   mEX = 0.0;
   mUX = 1.0;

   mFc1 = 1.0;
   mFc2 = 1.0;
   mAc1 = 1.0;
   mAc2 = 1.0;
   mPc1 = 0.0;
   mPc2 = 0.0;

   mSigma = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void TimeSeriesHarmonic::initialize()
{
   if (mFs != 0.0)
   {
      mTs = 1.0 / mFs;
   }
   else if (mTs != 0.0)
   {
      mFs = 1.0 / mTs;
   }


   mSigmaFlag = false;
   initializeNoise();

   mNumSamples = (int)(mDuration * mFs);
   mX = new double[mNumSamples];
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Guassian noise

// Initialize random distribution.
void TimeSeriesHarmonic::initializeNoise()
{
   // Set flag.
   mSigmaFlag = mSigma != 0.0;

   // Seed generator.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());

   // Set distribution parameters.
   std::normal_distribution<double>::param_type parm;
   if (mSigmaFlag) parm._Init(0.0, mSigma);
   else            parm._Init(0.0, 1.0);

   mRandomDistribution.param(parm);
}

// Get noise from random distribution.
double TimeSeriesHarmonic::getNoise()
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

void TimeSeriesHarmonic::show()
{
   printf("mDuration    %10.4f\n",mDuration);
   printf("mNumSamples  %10d\n",  mNumSamples);
   printf("mFs          %10.4f\n",mFs);
   printf("mTs          %10.4f\n",mTs);
   printf("mEX          %10.4f\n",mEX);
   printf("mUX          %10.4f\n",mUX);

   printf("mFc1         %10.4f\n",mFc1);
   printf("mFc2         %10.4f\n",mFc2);
   printf("mAc1         %10.4f\n",mAc1);
   printf("mAc2         %10.4f\n",mAc2);
   printf("mPc1         %10.4f\n",deg(mPc1));
   printf("mPc2         %10.4f\n",deg(mPc2));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TimeSeriesHarmonic::generate()
{
   //---------------------------------------------------------------------------
   // Initialize

   initialize();
   initializeNoise();

   //---------------------------------------------------------------------------
   // Generate harmonic signal with two frequencies.

   for (int k = 0; k < mNumSamples; k++)
   {
      // Time
      double tTime = mTs*k;

      // Signal
      double tX1 = mAc1*sin(DSP_2PI*mFc1*tTime + mPc1);
      double tX2 = mAc2*sin(DSP_2PI*mFc2*tTime + mPc2);

      // Store.
      mX[k] = tX1 + tX2;
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