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
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<> tRandomDistribution(0.0, aS->mSigma);

   for (int k = 0; k < aS->mNs; k++)
   {
         double tNoise  = tRandomDistribution(tRandomGenerator);
         double tSignal = (k <= aS->mKev1) ? 0.0 : aS->mOffset;
         aS->mX[k] = tSignal + tNoise;
   }
}

}//namespace
}//namespace
