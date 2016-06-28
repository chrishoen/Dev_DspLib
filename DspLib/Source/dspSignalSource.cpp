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
#include "dspSignalSource.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

SignalSource::SignalSource()
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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void SignalSource::initialize()
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
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Guassian noise

// Initialize random distribution.
void SignalSource::initializeNoise()
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
double SignalSource::getNoise()
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

void SignalSource::show()
{
   printf("mFs          %10.4f\n",mFs);
   printf("mTs          %10.4f\n",mTs);
   printf("mFp          %10.4f\n",mFp);
   printf("mTp          %10.4f\n",mTp);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

double SignalSource::advance()
{
   double tNoise = 0.0;
   double tX = 0.0;

   //Time
   mT += mTs;

   // Noise
   tNoise = getNoise();

   // Signal
   tX = sin(DSP_2PI*mFp*mT);

   // Sample
   mX = mAmplitude*tX + tNoise + mOffset;

   // Done
   return mX;
}

}//namespace