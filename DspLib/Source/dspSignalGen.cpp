/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <math.h>
#include <random>

#include "dspDefs.h"
#include "dspSignalGen.h"

namespace Dsp
{
namespace SignalGen
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Guassian noise

static bool mSigmaFlag = false;
static std::mt19937 mRandomGenerator;
static std::normal_distribution<double> mRandomDistribution;

// Initialize random distribution.
static void initializeNoise(Signal* aS)
{
   // Set flag.
   mSigmaFlag = aS->mSigma != 0.0;

   // Seed generator.
   std::random_device tRandomDevice;
   mRandomGenerator.seed(tRandomDevice());

   // Set distribution parameters.
   std::normal_distribution<double>::param_type parm;
   if (mSigmaFlag) parm._Init(0.0, aS->mSigma);
   else            parm._Init(0.0, 1.0);

   mRandomDistribution.param(parm);
}

// Get noise from random distribution.
static double getNoise()
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

void constant(Signal* aS)
{
   // Initialize
   initializeNoise(aS);

   double tNoise = 0.0;
   double tX = 0.0;

   // For all samples
   for (int k = 0; k < aS->mNs; k++)
   {
      // Noise
      tNoise = getNoise();

      // Signal
      tX = 0.0;

      // Sample
      aS->mX[k] = aS->mScale*tX +tNoise + aS->mOffset;;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void impulse(Signal* aS)
{
   // Initialize
   initializeNoise(aS);

   double tNoise  = 0.0;
   double tX = 0.0;

   // For all samples
   for (int k = 0; k < aS->mNs; k++)
   {
      // Noise
      tNoise = getNoise();

      // Signal
      if (k != aS->mKev1)
      {
         tX = 0.0;
      }
      else
      {
         tX = aS->mFs;
         tX = 1.0;
      }

      // Sample
      aS->mX[k] = aS->mScale*tX +tNoise + aS->mOffset;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate step random, normal

void step(Signal* aS)
{
   // Initialize
   initializeNoise(aS);

   double tNoise  = 0.0;
   double tX = 0.0;

   // For all samples
   for (int k = 0; k < aS->mNs; k++)
   {
      // Noise
      tNoise = getNoise();

      // Signal
      if (k < aS->mKev1)
      {
         tX = 0.0;
      }
      else if (aS->mKev1 < k)
      {
         tX = 1.0;
      }
      else
      {
      }

      // Sample
      aS->mX[k] = aS->mScale*tX +tNoise + aS->mOffset;;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate ramp random, normal

void ramp(Signal* aS)
{
   // Initialize
   initializeNoise(aS);

   double tNoise  = 0.0;
   double tX = 0.0;

   // For all samples
   for (int k = 0; k < aS->mNs; k++)
   {
      // Noise
      tNoise = getNoise();

      // Signal
      if (k < aS->mKev1)
      {
         tX = 0.0;
      }
      else if (aS->mKev1 <= k && k < aS->mKev2)
      {
         tX += aS->mDeltaX;
      }
      else
      {
      }

      // Sample
      aS->mX[k] = aS->mScale*tX +tNoise + aS->mOffset;;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate sinusoid random, normal

void sinusoid(Signal* aS)
{
   // Initialize
   initializeNoise(aS);

   double tNoise  = 0.0;
   double tX = 0.0;
   double tT = 0.0;

   // For all samples
   for (int k = 0; k < aS->mNs; k++)
   {
      // Noise
      tNoise = getNoise();

      // Time
      tT = k*aS->mTs;

      // Signal
      tX = sin(DSP_2PI*aS->mFp*tT);

      // Sample
      aS->mX[k] = aS->mScale*tX +tNoise + aS->mOffset;;
   }
}

}//namespace
}//namespace
