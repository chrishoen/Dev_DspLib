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
class AlphaThree
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.


   // Input variable.
   double mY;

   // Filter state output variables.
   double mXX;
   double mXV;
   double mXA;

   // Filter parameters.
   double mAlpha;
   double mBeta;
   double mGamma;
   double mDT;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize with lambda,DT (tracking index, time increment).

   void initialize(double aLambda,double aDT)
   {
      // Calculate filter parameters.
      double L  = aLambda;
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

      // Store parameter variables.
      mAlpha = A;
      mBeta  = B;
      mGamma = G;
      mDT    = aDT;

      // Initialize output variables.
      mY=0.0;
      mXX=0.0;
      mXV=0.0;
      mXA=0.0;

   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Put input value, return filtered output.

   double put(double aY)
   {
      // Store input
      mY = aY;

      // Implement the filter.
      double a   = mAlpha;
      double b   = mBeta;
      double g   = mGamma;
      double dt  = mDT;
      double dt2 = dt*dt;

      double xm = aY;
      double xk = mXX;
      double vk = mXV;
      double ak = mXA;

      mXX = xk*(1-a)    + vk*(1-a)*dt + ak*(1-a)*dt2/2  + xm*a;
      mXV = xk*(-b/dt)  + vk*(1-b)    + ak*(1-b/2)*dt   + xm*b/dt;
      mXA = xk*(-g/dt2) + vk*(-g/dt)  + ak*(1-g/2)      + xm*g/dt2;

      // Return output.
      return mXX;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace

