/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dsp_math.h"
#include "dspStatistics.h"
#include "dspTimeSeriesHarmonic.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

TimeSeriesHarmonic::TimeSeriesHarmonic()
{
   reset();
}

void TimeSeriesHarmonic::reset()
{
   BaseClass::reset();

   mFc1 = 1.0;
   mFc2 = 1.0;
   mAc1 = 1.0;
   mAc2 = 1.0;
   mPc1 = 0.0;
   mPc2 = 0.0;

   mFcRandom = 0.0;
   mAcRandom = 0.0;
   mPcRandom = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void TimeSeriesHarmonic::initialize()
{
   BaseClass::initialize();
}  

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void TimeSeriesHarmonic::show()
{
   BaseClass::show();

   printf("mFc1         %10.4f\n",mFc1);
   printf("mFc2         %10.4f\n",mFc2);
   printf("mAc1         %10.4f\n",mAc1);
   printf("mAc2         %10.4f\n",mAc2);
   printf("mPc1         %10.4f\n",deg(mPc1));
   printf("mPc2         %10.4f\n",deg(mPc2));

   printf("mFcRandom    %10.4f\n",mFcRandom);
   printf("mAcRandom    %10.4f\n",mAcRandom);
   printf("mPcRandom    %10.4f\n",deg(mPcRandom));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TimeSeriesHarmonic::generate()
{
   //---------------------------------------------------------------------------
   // Initialize

   initialize();

   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());

   std::uniform_real_distribution<double> tRandomDistributionFc1(mFc1-mFcRandom/2.0,mFc1+mFcRandom/2.0);
   std::uniform_real_distribution<double> tRandomDistributionFc2(mFc2-mFcRandom/2.0,mFc2+mFcRandom/2.0);
   std::uniform_real_distribution<double> tRandomDistributionAc1(mAc1-mAcRandom/2.0,mAc1+mAcRandom/2.0);
   std::uniform_real_distribution<double> tRandomDistributionAc2(mAc2-mAcRandom/2.0,mAc2+mAcRandom/2.0);
   std::uniform_real_distribution<double> tRandomDistributionPc1(mPc1-mPcRandom/2.0,mPc1+mPcRandom/2.0);
   std::uniform_real_distribution<double> tRandomDistributionPc2(mPc2-mPcRandom/2.0,mPc2+mPcRandom/2.0);

   double tFc1 = tRandomDistributionFc1(tRandomGenerator);
   double tFc2 = tRandomDistributionFc2(tRandomGenerator);
   double tAc1 = tRandomDistributionAc1(tRandomGenerator);
   double tAc2 = tRandomDistributionAc2(tRandomGenerator);
   double tPc1 = tRandomDistributionPc1(tRandomGenerator);
   double tPc2 = tRandomDistributionPc2(tRandomGenerator);

   //---------------------------------------------------------------------------
   // Generate harmonic signal with two frequencies.

   for (int k = 0; k < mNumSamples; k++)
   {
      // Time
      double tTime = mTs*k;

      // Signal
      double tX1 = tAc1*sin(DSP_2PI*tFc1*tTime + tPc1);
      double tX2 = tAc2*sin(DSP_2PI*tFc2*tTime + tPc2);

      // Store.
      mX[k] = tX1 + tX2;
   }

   //---------------------------------------------------------------------------
   // Normalize to get the desired expectation and uncertainty.

   normalize();
}

}//namespace