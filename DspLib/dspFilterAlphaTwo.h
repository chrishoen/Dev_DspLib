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
// Alpha Beta filter, second order iir position/velocity filter. This is a 
// steady state kalman filter that gives a smoothed estimate of a target
// position and velocity.
// For documentation, google
// "ADA255832" or
// "FIXED-GAIN, TWO-STAGE ESTIMATORS FOR TRACKING MANEUVERING TARGETS"
// For documentation, google wikipedia
// "Alpha beta filter"

template <typename real_t>
class AlphaTwo
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Input variable.
   real_t mY;

   // Filter state output variables.
   real_t mXX;
   real_t mXV;

   // Filter parameters.
   real_t mAlpha;
   real_t mBeta;
   real_t mDT;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize with lambda,DT (tracking index, time increment).

   void initialize(real_t aLambda,real_t aDT)
   {
      // Calculate filter parameters.
      real_t L  = aLambda;
      real_t L2 = L*L;

      real_t r  = (4 + L-sqrt(8*L + L2))/4;
      real_t r2 = r*r;

      real_t A  = 1-r2;
      real_t B  = 2*(2-A) - 4*sqrt(1-A);

      // Store parameter variables.
      mAlpha = A;
      mBeta  = B;
      mDT    = aDT;

      // Initialize output variables.
      mY=0.0;
      mXX=0.0;
      mXV=0.0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Put input value, return filtered output.

   real_t put(real_t aY)
   {
      // Store input
      mY = aY;

      // Implement the filter.
      real_t a   = mAlpha;
      real_t b   = mBeta;
      real_t dt  = mDT;

      real_t xm = aY;
      real_t xk = mXX;
      real_t vk = mXV;

      mXX = xk*(1-a)    + vk*(1-a)*dt + xm*a;
      mXV = xk*(-b/dt)  + vk*(1-b)    + xm*b/dt;

      // Return output.
      return mXX;
   }
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace

