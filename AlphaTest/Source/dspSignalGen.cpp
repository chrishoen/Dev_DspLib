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

static const double cPI = 3.14159265358979323846264338327950288419716939937510;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate step random, normal

void step(Signal* aS)
{
   bool tSigmaFlag = aS->mSigma != 0.0;
   double tSigma = aS->mSigma;
   if (tSigma==0.0) tSigma=1.0;

   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<> tRandomDistribution(0.0, tSigma);

   double tNoise  = 0.0;
   double tX = 0.0;

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

      aS->mX[k] = tX + tNoise + aS->mOffset;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate step random, normal

void random(Signal* aS)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<> tRandomDistribution(0.0, aS->mSigma);

   double tNoise  = tRandomDistribution(tRandomGenerator);
   double tX = 0.0;

   for (int k = 0; k < aS->mNs; k++)
   {
      tNoise  = tRandomDistribution(tRandomGenerator);

      if (k < aS->mKev1)
      {
         tX = 0.0;
      }
      else if (aS->mKev1 < k && k < aS->mKev2)
      {
         tX += aS->mDeltaX;
      }
      else
      {
      }

      aS->mX[k] = tX + tNoise + aS->mOffset;
   }
}

}//namespace
}//namespace
