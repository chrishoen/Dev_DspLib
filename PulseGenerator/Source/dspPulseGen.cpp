/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <math.h>
#include <random>

#include "dspPulseGen.h"

namespace Dsp
{
namespace PulseGen
{

static const double cPI = 3.14159265358979323846264338327950288419716939937510;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate constant pulse sequence

void gen11(PdwSequence* aS)
{
   for (int k = 1; k < aS->mNs; k++)
   {
      Pdw tPdw;
      tPdw.mIndex     = k;
      tPdw.mToa       = k * aS->mTs;
      tPdw.mAmplitude = 1.0;

      if (k % aS->mNm == 0)
      {
         aS->putPdw(&tPdw);
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate pulse sequence, geometric distribution

void gen21(PdwSequence* aS)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::geometric_distribution<int> tRandomDistribution(aS->mTm);

   int kevent = tRandomDistribution(tRandomGenerator);
   for (int k = 0; k < aS->mNs; k++)
   {
      Pdw tPdw;
      tPdw.mIndex     = k;
      tPdw.mToa       = k * aS->mTs;
      tPdw.mAmplitude = 1.0;

      if (k >= kevent)
      {
         aS->putPdw(&tPdw);
         kevent += tRandomDistribution(tRandomGenerator);
      }
   }
}


   
}//namespace
}//namespace
