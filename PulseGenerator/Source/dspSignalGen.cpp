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
// Generate sin wave

void gen1(Signal* aSS)
{
   for (int k = 0; k < aSS->mNs; k++)
   {
         double t = k * aSS->mTs;
         aSS->mX[k] = sin(2.0 * cPI * aSS->mFp * t);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate random, uniform

void gen21(Signal* aSS)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::uniform_real_distribution<> tRandomDistribution(-1.0, 1.0);

   for (int k = 0; k < aSS->mNs; k++)
   {
         double t = k * aSS->mTs;
         aSS->mX[k] = tRandomDistribution(tRandomGenerator);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate random, normal

void gen22(Signal* aSS)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<> tRandomDistribution(0.0, 1.0);

   for (int k = 0; k < aSS->mNs; k++)
   {
         double t = k * aSS->mTs;
         aSS->mX[k] = tRandomDistribution(tRandomGenerator);
   }
}

   
}//namespace
}//namespace
