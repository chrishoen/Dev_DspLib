/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspPulseSignalGen.h"

namespace Dsp
{
namespace PulseSignalGen
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
// Generate discrete pulses, geometric distribution

void gen34(Signal* aS)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::geometric_distribution<int> tRandomDistribution(aS->mTp);

   int kevent = tRandomDistribution(tRandomGenerator);
   for (int k = 0; k < aS->mNs; k++)
   {
      if (k >= kevent)
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
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate step, constant

void gen51(Signal* aS)
{
   for (int k = 0; k < aS->mNs; k++)
   {
      aS->mX[k] = (k <= aS->mKev1) ? 0.0 : 1.0;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate random, normal

void gen52(Signal* aS)
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
