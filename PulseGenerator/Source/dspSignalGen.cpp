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

void gen11(Signal* aS)
{
   for (int k = 0; k < aS->mNs; k++)
   {
         double t = k * aS->mTs;
         aS->mX[k] = sin(2.0 * cPI * aS->mFp * t);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate random, uniform

void gen21(Signal* aS)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::uniform_real_distribution<> tRandomDistribution(-1.0, 1.0);

   for (int k = 0; k < aS->mNs; k++)
   {
         double t = k * aS->mTs;
         aS->mX[k] = tRandomDistribution(tRandomGenerator);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate random, normal

void gen22(Signal* aS)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<> tRandomDistribution(0.0, 1.0);

   for (int k = 0; k < aS->mNs; k++)
   {
         double t = k * aS->mTs;
         aS->mX[k] = tRandomDistribution(tRandomGenerator);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate discrete pulses, constant

void gen31(Signal* aS)
{
   for (int k = 0; k < aS->mNs; k++)
   {
      aS->mX[k] = (k % aS->mNp <= aS->mNp1) ? 1.0 : 0.0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate discrete pulses, poisson distribution

void gen32(Signal* aS)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::poisson_distribution<> tRandomDistribution(aS->mNp);

   int kevent = tRandomDistribution(tRandomGenerator);
   for (int k = 0; k < aS->mNs; k++)
   {
      if (k == kevent)
      {
         aS->mX[k] = 1.0;
         kevent += tRandomDistribution(tRandomGenerator);
      }
      else
      {
         aS->mX[k] = 0.0;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate discrete pulses, exponetial distribution for interarrival times

void gen33(Signal* aS)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::exponential_distribution<> tRandomDistribution(aS->mFp);

   double tToa = tRandomDistribution(tRandomGenerator);
   for (int k = 0; k < aS->mNs; k++)
   {
      double tTime = k * aS->mTs;
      if (tTime >= tToa)
      {
         aS->mX[k] = 1.0;
         tToa += tRandomDistribution(tRandomGenerator);
      }
      else
      {
         aS->mX[k] = 0.0;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate pulse train

void gen41(Signal* aS)
{
   for (int k = 0; k < aS->mNs; k++)
   {
      double t = k * aS->mTs;
      double x = sin(2.0 * cPI * aS->mFp * t);
      aS->mX[k] = (k % aS->mNm <= aS->mNm1) ? x : 0.0;
   }
}

   
}//namespace
}//namespace
