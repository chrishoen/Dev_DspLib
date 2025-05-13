#pragma once
/*==============================================================================
alpha, beta, gamma filters
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{
namespace Filter
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Alpha filter, first order position filter. This is a steady state kalman
// filter that gives a smoothed estimate of a target position.
// For documentation, google
// "ADA255832" or
// "FIXED-GAIN, TWO-STAGE ESTIMATORS FOR TRACKING MANEUVERING TARGETS"
// For documentation, google wikipedia
// "Alpha beta filter"
//
template <typename real_t>
class AlphaOne
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Input variable.
   real_t mY;

   // Output variables.
   real_t mXX;

   // Filter parameters
   real_t mAlpha;

   // True for first sample.
   bool mFirstFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize from alpha.

   void initializeFromAlpha(double aAlpha)
   {
      mAlpha = (real_t)aAlpha;
      mY   = 0.0;
      mXX  = 0.0;
      mFirstFlag = true;
      return;
      printf("AlphaOne::initializeFromAlpha %8.8f\n", mAlpha);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize from noise ratio, process sigma over sensor sigma.
   // Calculate the tracking index from the noise ratio and calculate
   // alpha, beta, gamma from the tracking index.

   void initializeFromNoiseRatio (double aNoiseRatio, double aDT)
   {
      // Calculate filter parameters.
      double L  = aNoiseRatio*aDT*aDT;
      double L2 = L*L;
      double A = (-L2 + L*sqrt(16 + L2))/8;
      mAlpha = (real_t)A;

      // Initialize filter variables.
      mY   = 0.0;
      mXX  = 0.0;
      mFirstFlag = true;
      return;
      printf("AlphaOne::initializeFromNoiseRatio %8.8f $ %8.8f  %8.8f $  %8.8f\n",
         mAlpha, aNoiseRatio, aDT, L);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize from step response time and threshold.

   void initializeFromStep(double aTs, double aStepTime, double aStepThresh = 0.9)
   {
      if (aStepTime < aTs) aStepTime = aTs;
      if (aStepThresh > 1) aStepThresh = 1;
      if (aStepThresh < 0) aStepThresh = 0;

      double n = aStepTime / aTs;
      double c = 1 - aStepThresh;
      double b = exp(log(c) / n);
      double a = 1 - b;

      mAlpha = (real_t)a;
      mY = 0.0;
      mXX = 0.0;
      mFirstFlag = true;
      return;
      printf("AlphaOne::initializeFromStep %8.8f  $ %8.8f  %8.8f %8.8f\n", 
         mAlpha, aTs, aStepTime, aStepThresh);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Set the first flag true.

   void setFirst()
   {
      mY   = 0.0;
      mXX  = 0.0;
      mFirstFlag = true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Put input value, return filtered output.

   real_t put(real_t aY)
   {
      if (mFirstFlag)
      {
         mFirstFlag = false;
         mXX = aY;
      }
      // Store input.
      mY  = aY;

      // Implement the filter.
      mXX = mXX + mAlpha*(mY - mXX);

      return mXX;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Put input value, return filtered output.

   real_t putBool(bool aCondition)
   {
      if (aCondition) return put(1.0);
      else            return put(0.0);
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace

