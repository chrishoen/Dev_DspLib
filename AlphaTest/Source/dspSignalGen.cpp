/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <math.h>
#include <random>

#include "dspSignalGen.h"

namespace Dsp
{
namespace SignalGen
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

void constant(Signal* aS)
{
   // Random
   bool tSigmaFlag = aS->mSigma != 0.0;

   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<double>::param_type parm;

   if (tSigmaFlag) parm._Init(0.0, aS->mSigma);
   else            parm._Init(0.0, 1.0);

   std::normal_distribution<double> tRandomDistribution(parm);

   double tNoise  = 0.0;
   double tX = 0.0;

   // Signal
   for (int k = 0; k < aS->mNs; k++)
   {
      if (tSigmaFlag)
      {
         tNoise = tRandomDistribution(tRandomGenerator);
      }

      tX = 0.0;

      aS->mX[k] = aS->mScale*tX +tNoise + aS->mOffset;;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void impulse(Signal* aS)
{
   // Random
   bool tSigmaFlag = aS->mSigma != 0.0;

   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<double>::param_type parm;

   if (tSigmaFlag) parm._Init(0.0, aS->mSigma);
   else            parm._Init(0.0, 1.0);

   std::normal_distribution<double> tRandomDistribution(parm);

   double tNoise  = 0.0;
   double tX = 0.0;

   // Signal
   for (int k = 0; k < aS->mNs; k++)
   {
      if (tSigmaFlag)
      {
         tNoise = tRandomDistribution(tRandomGenerator);
      }

      if (k != aS->mKev1)
      {
         tX = 0.0;
      }
      else
      {
         tX = aS->mFs;
         tX = 1.0;
      }

      aS->mX[k] = aS->mScale*tX +tNoise + aS->mOffset;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate step random, normal

void step(Signal* aS)
{
   // Random
   bool tSigmaFlag = aS->mSigma != 0.0;

   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<double>::param_type parm;

   if (tSigmaFlag) parm._Init(0.0, aS->mSigma);
   else            parm._Init(0.0, 1.0);

   std::normal_distribution<double> tRandomDistribution(parm);

   double tNoise  = 0.0;
   double tX = 0.0;

   // Signal
   for (int k = 0; k < aS->mNs; k++)
   {
      if (tSigmaFlag)
      {
         tNoise = tRandomDistribution(tRandomGenerator);
      }

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

      aS->mX[k] = aS->mScale*tX +tNoise + aS->mOffset;;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate ramp random, normal

void ramp(Signal* aS)
{
   // Random
   bool tSigmaFlag = aS->mSigma != 0.0;

   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<double>::param_type parm;

   if (tSigmaFlag) parm._Init(0.0, aS->mSigma);
   else            parm._Init(0.0, 1.0);

   std::normal_distribution<double> tRandomDistribution(parm);

   double tNoise  = 0.0;
   double tX = 0.0;

   // Signal
   for (int k = 0; k < aS->mNs; k++)
   {
      if (tSigmaFlag)
      {
         tNoise = tRandomDistribution(tRandomGenerator);
      }

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

      aS->mX[k] = aS->mScale*tX +tNoise + aS->mOffset;;
   }
}

}//namespace
}//namespace
