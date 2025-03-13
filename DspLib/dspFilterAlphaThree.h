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
// Alpha Beta Gamma filter, third order iir position/velocity/acceleration
// filter. This is a steady state kalman filter that gives a smoothed estimate
// of a target position, velocity , and acceleration.
// For documentation, google
// "ADA255832" or
// "FIXED-GAIN, TWO-STAGE ESTIMATORS FOR TRACKING MANEUVERING TARGETS"
// For documentation, google wikipedia
// "Alpha beta filter"

template<typename real_t>
class AlphaThreeT
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
   real_t mXA;

   // Filter parameters.
   real_t mAlpha;
   real_t mBeta;
   real_t mGamma;
   real_t mDT;

   // Filter coefficients.
   real_t mKK1,mKK2,mKK3;

   // Other filter coefficients.
   real_t mK11,mK12,mK13,mK14;
   real_t mK21,mK22,mK23,mK24;
   real_t mK31,mK32,mK33,mK34;

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
      double A2  = A*A;
      double B  = A2/(2-A);
      double B2 = B*B;
      double G  = B2/(2*A);
      double DT = aDT;
      double DT2 = DT*DT;

      // Filter coefficients.
      mKK1 = (real_t)(DT2/2);
      mKK2 = (real_t)(B/DT);
      mKK3 = (real_t)(G/(DT2));    // same as kalman
   // mKK3 = (real_t)(G/(2*DT2));  // same as matlab
   // mKK3 = (real_t)(2*G/DT2);    // same as wikipedia

      // Other Filter coefficients.
      mK11 = (real_t)(1-A);     mK12 = (real_t)((1-A)*DT);mK13 = (real_t)((1-A)*DT2/2);  mK14 = (real_t)(A);
      mK21 = (real_t)(-B/DT);   mK22 = (real_t)(1-B);     mK23 = (real_t)((1-B/2)*DT);   mK24 = (real_t)(B/DT);
      mK31 = (real_t)(-G/DT2);  mK32 = (real_t)(-G/DT);   mK33 = (real_t)(1-G/2);        mK34 = (real_t)(G/DT2);

      // Store parameter variables.
      mAlpha = (real_t)A;
      mBeta  = (real_t)B;
      mGamma = (real_t)G;
      mDT    = (real_t)DT;

      // Initialize output variables.
      mY=0.0;
      mXX=0.0;
      mXV=0.0;
      mXA=0.0;
      mFirstFlag = true;

      printf("AlphaThree::initializeFromAlpha %8.8f %8.8f  %8.8f $ %8.8f\n",
         mAlpha, mBeta, mGamma, aDT);
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

      double b  = L/2 - 3;
      double b2 = b*b;
      double b3 = b*b*b;
      double c  = L/2 + 3;
      double d  = -1;

      double p  = c - b2/3;
      double p3 = p*p*p;
      double q  = 2*b3/27 - b*c/3 + d;
      double q2 = q*q;

      double v  = sqrt(q2 + 4*p3/27);
      double z  = -pow(q + v/2, 1.0/3.0);

      double s  = z - p/(3*z) - b/3;
      double s2 = s*s;

      double A  = 1-s2;
      double B  = 2*pow(1-s,2);
      double B2 = B*B;
      double G  = B2/(2*A);
      double DT = aDT;
      double DT2 = DT*DT;

      // Filter coefficients.
      mKK1 = (real_t)(DT2/2);
      mKK2 = (real_t)(B/DT);
      mKK3 = (real_t)(G/(DT2));    // same as kalman
   // mKK3 = (real_t)(G/(2*DT2));  // same as matlab
   // mKK3 = (real_t)(2*G/DT2);    // same as wikipedia

      // Other filter coefficients.
      mK11 = (real_t)(1-A);     mK12 = (real_t)((1-A)*DT);mK13 = (real_t)((1-A)*DT2/2);  mK14 = (real_t)(A);
      mK21 = (real_t)(-B/DT);   mK22 = (real_t)(1-B);     mK23 = (real_t)((1-B/2)*DT);   mK24 = (real_t)(B/DT);
      mK31 = (real_t)(-G/DT2);  mK32 = (real_t)(-G/DT);   mK33 = (real_t)(1-G/2);        mK34 = (real_t)(G/DT2);

      // Store parameter variables.
      mAlpha = (real_t)A;
      mBeta  = (real_t)B;
      mGamma = (real_t)G;
      mDT    = (real_t)DT;

      // Initialize output variables.
      mY=0.0;
      mXX=0.0;
      mXV=0.0;
      mXA=0.0;
      mFirstFlag = true;

      printf("AlphaThree::initializeFromNoiseRatio %8.8f %8.8f %8.8f $ %8.8f  %8.8f $  %8.8f\n",
         mAlpha, mBeta, mGamma, aNoiseRatio, aDT, L);
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
         mXA = 0;
      }
      // Store input
      mY = aY;

      // Implement the filter. 6 mul,7 add
      real_t xm = aY;
      real_t xs = mXX;
      real_t vs = mXV;
      real_t as = mXA;
      
      real_t xp = xs + mDT*vs + mKK1*as;
      real_t vp = vs + mDT*as;
      real_t rk = xm - xp;

      mXX = xp + mAlpha*rk;
      mXV = vp + mKK2*rk;
      mXA = as + mKK3*rk;

      // Return output.
      return mXX;
   }

   real_t put22(real_t aY)
   {
      // Initial value.
      if (mFirstFlag)
      {
         mFirstFlag = false;
         mXX = aY;
         mXV = 0;
         mXA = 0;
      }
      // Store input
      mY = aY;

      // Implement the filter. 12 mul,9 add
      real_t xm = aY;
      real_t xk = mXX;
      real_t vk = mXV;
      real_t ak = mXA;

      mXX = mK11*xk + mK12*vk + mK13*ak + mK14*xm;
      mXV = mK21*xk + mK22*vk + mK23*ak + mK24*xm;
      mXA = mK31*xk + mK32*vk + mK33*ak + mK34*xm;

      // Return output.
      return mXX;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace


