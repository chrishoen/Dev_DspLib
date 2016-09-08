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
#include "dspSignalSourceLPGN.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

SignalSourceLPGN::SignalSourceLPGN()
{
   reset();
}

void SignalSourceLPGN::reset()
{
   mT  = 0.0;
   mX  = 0.0;
   mFs = 1.0;
   mTs = 1.0 / mFs;
   mFp = 1.0;
   mTp = 1.0 / mFp;

   mAmplitude = 1.0;
   mSigma = 0.0;
   mOffset = 0.0;

   mAlphaOneAP1 = 1.0;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void SignalSourceLPGN::initialize()
{
   mT=0.0;
   mX=0.0;

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

}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Guassian noise

// Initialize random distribution.
void SignalSourceLPGN::initializeNoise()
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
double SignalSourceLPGN::getNoise()
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

void SignalSourceLPGN::show()
{
   printf("mFs          %10.4f\n",mFs);
// printf("mTs          %10.4f\n",mTs);
   printf("mFp          %10.4f\n",mFp);
// printf("mTp          %10.4f\n",mTp);
   printf("mSigma       %10.4f\n",mSigma);
   printf("mOffset      %10.4f\n",mOffset);
   printf("mAmplitude   %10.4f\n",mAmplitude);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

double SignalSourceLPGN::advance(double tTime)
{
   //Time
   if (tTime != -1.0)
   {
      mT = tTime;
   }
   else
   {
      mT += mTs;
   }

   double tNoise = 0.0;

   // Noise
   tNoise = getNoise();

   // Sample
   mX = mAmplitude*tNoise + mOffset;

   // Low pass filter
   mAlphaOne1.put(mX);
   mAlphaOne2.put(mAlphaOne1.mXX);
   mEX = mAlphaOne2.mXX;
   // Done
   return mX;
}

}//namespace