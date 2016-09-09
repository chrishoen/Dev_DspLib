/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dspDefs.h"
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

   mScale = 1.0;
   mSigma = 0.0;
   mOffset = 0.0;

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
   printf("mSigma       %10.4f\n",mSigma);
   printf("mOffset      %10.4f\n",mOffset);
   printf("mScale   %10.4f\n",mScale);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Normalize

void TimeSeriesLPGN::normalize()
{
   // Get min and max
   double xMin = 0.0;
   double xMax = 0.0;

   for (int k = 0; k < mNumSamples; k++)
   {
      double x = mX[k];
      if (x < xMin) xMin = x;
      if (x > xMax) xMax = x;
   }

   // Get scale and offset
   if (xMin != xMax)
   {
      double scale = 1.0 / ((xMax - xMin) / 2.0);
      double offset = (xMax + xMin) / 2.0;

      // Adjust signal to be -1 <= x[k] <= 1
      for (int k = 0; k < mNumSamples; k++)
      {
         double x = mX[k];
         double xa = scale * (x - offset);
         mX[k] = mScale*xa;
      }
   }
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TimeSeriesLPGN::generate()
{
   initialize();
   initializeNoise();

   for (int k = 0; k < mNumSamples; k++)
   {

      double tNoise = 0.0;

      // Noise
      tNoise = getNoise();

      // Sample
      double tX = tNoise + mOffset;

      // Low pass filter
      mAlphaOne1.put(tX);
      mAlphaOne2.put(mAlphaOne1.mXX);
      double tEX = mAlphaOne2.mXX;
      // Done
      mX[k] = tEX;
   }
}

}//namespace