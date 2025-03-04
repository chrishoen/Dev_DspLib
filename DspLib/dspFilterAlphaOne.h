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
template<typename real_t>
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
   // Methods. Initialize from lambda (tracking index).

   void initialize(real_t aLambda)
   {
      // Calculate filter parameters.
      real_t L  = aLambda;
      real_t L2 = L*L;
      real_t A = (-L2 + L*sqrt(16 + L2))/8;
      mAlpha = A;

      // Initialize filter variables.
      mY   = 0.0;
      mXX  = 0.0;
      mFirstFlag = true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   //  Methods. Initialize from alpha.

   void initializeFromAlpha(real_t aAlpha)
   {
      mAlpha = aAlpha;
      mY   = 0.0;
      mXX  = 0.0;
      mFirstFlag = true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   //  Methods. Initialize from lambda (tracking index).

   void initializeFromLambda(real_t aLambda)
   {
      initialize(aLambda);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   //  Methods. Initialize from step response time and threshold.

   void initializeFromStep(real_t aTs, real_t aStepTime, real_t aStepThresh)
   {
      if (aStepTime < aTs) aStepTime = aTs;
      if (aStepThresh > 1) aStepThresh = 1;
      if (aStepThresh < 0) aStepThresh = 0;

      real_t n = aStepTime / aTs;
      real_t c = 1 - aStepThresh;
      real_t b = exp(log(c) / n);
      real_t a = 1 - b;

      mAlpha = a;
      mY = 0.0;
      mXX = 0.0;
      mFirstFlag = true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   //  Methods. Set the first flag true.

   void setFirst()
   {
      mY   = 0.0;
      mXX  = 0.0;
      mFirstFlag = true;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   //  Methods. Put input value, return filtered output.

   real_t put(real_t aY)
   {
      if (mFirstFlag)
      {
         mFirstFlag = false;
         mXX = aY;
      }

      mY  = aY;

      real_t a = mAlpha;

      mXX = (1-a)*mXX + a*mY;

      return mXX;
   }

   real_t put(bool aCondition)
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

