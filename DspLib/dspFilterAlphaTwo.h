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

   // Filter parameters.
   real_t mBetaDivDT;

   // If true then first sample.
   bool mFirstFlag;
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize from alpha.

   void initializeFromAlpha(double aAlpha, double aDT)
   {
      // Calculate filter parameters.
      double A  = aAlpha;
      double B  = 2*(2-A) - 4*sqrt(1-A);
      double DT = aDT;
      // Store parameter variables.
      mAlpha = (real_t)A;
      mBeta  = (real_t)B;
      mDT    = (real_t)DT;
      mBetaDivDT = (real_t)(B/DT);

      // Initialize output variables.
      mY=0.0;
      mXX=0.0;
      mXV=0.0;
      mFirstFlag = true;
      printf("AlphaTwo::initializeFromAlpha %8.8f %8.8f $ %8.8f\n",
         mAlpha, mBeta, aDT);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize from noise ratio, process sigma over sensor sigma.
   // Calculate the tracking index from the noise ratio and calculate
   // alpha, beta, gamma from the tracking index.

   void initializeFromNoiseRatio(double aNoiseRatio,double aDT)
   {
      // Calculate filter parameters.
      double L  = aNoiseRatio*aDT*aDT;
      double L2 = L*L;

      double r  = (4 + L-sqrt(8*L + L2))/4;
      double r2 = r*r;

      double A  = 1-r2;
      double B  = 2*(2-A) - 4*sqrt(1-A);
      double DT = aDT;

      // Store parameter variables.
      mAlpha = (real_t)A;
      mBeta  = (real_t)B;
      mDT    = (real_t)DT;
      mBetaDivDT = (real_t)(B/DT);

      // Initialize output variables.
      mY=0.0;
      mXX=0.0;
      mXV=0.0;
      mFirstFlag = true;
      printf("AlphaTwo::initializeFromNoiseRatio %8.8f %8.8f $ %8.8f  %8.8f $  %8.8f\n",
         mAlpha, mBeta, aNoiseRatio, aDT, L);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Put input value, return filtered output.

   real_t put(real_t aY)
   {
      // Initial value.
      if (mFirstFlag)
      {
         mFirstFlag = false;
         mXX = aY;
         mXV = 0;
      }
      // Store input
      mY = aY;

      // Implement the filter. 3 mul, 4 add.
      real_t xm = aY;
      real_t xs = mXX;
      real_t vs = mXV;

      real_t xp = xs + mDT*vs;
      real_t vp = vs;
      real_t rk = xm - xp;

      mXX = xp + mAlpha*rk;
      mXV = vp + mBetaDivDT*rk;

      // Return output.
      return mXX;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace

