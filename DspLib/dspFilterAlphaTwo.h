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
class AlphaTwoT
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

   // Filter coefficients.
   real_t mA1,mA2,mA3;
   real_t mB1,mB2,mB3;
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize with lambda,DT (tracking index, time increment).

   void initialize(real_t aLambda,real_t aDT)
   {
      // Calculate filter parameters.
      double L  = aLambda;
      double L2 = L*L;

      double R  = (4 + L-sqrt(8*L + L2))/4;
      double R2 = R*R;

      double A  = 1-R2;
      double B  = 2*(2-A) - 4*sqrt(1-A);

      // Store parameter variables.
      mAlpha = (real_t)(A);
      mBeta  = (real_t)(B);
      mDT    = (real_t)(aDT);

      // Calculate filter coefficients.
      mA1 = (real_t)(1-A);
      mA2 = (real_t)((1-A)*aDT);
      mA3 = (real_t)(A);
      mB1 = (real_t)(-B/aDT);
      mB2 = (real_t)(1-B);
      mB3 = (real_t)(B/aDT);

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

      // Implement the filter from the coefficients.
      mXX = mA1*mXX + mA2*mXV + mA3*aY;
      mXV = mB1*mXX + mB2*mXV + mB3*aY;
      
      // Return output.
      return mXX;
   }
};


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace

#if 0
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
#endif