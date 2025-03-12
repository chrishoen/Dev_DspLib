/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dsp_math.h"
#include "dspFilterAlpha.h"

namespace Dsp
{
namespace Filter
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize from alpha.

void AlphaOne::initializeFromAlpha(double aAlpha)
{
   mAlpha = aAlpha;
   mY   = 0.0;
   mXX  = 0.0;
   mFirstFlag = true;
   printf("AlphaOne::initializeFromAlpha %8.8f\n", mAlpha);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize from sigma ratio, process sigma over noise sigma.

void AlphaOne::initializeFromSigmaRatio (double aSigmaRatio, double aDT)
{
   // Calculate filter parameters.
   double L  = aSigmaRatio*aDT*aDT;
   double L2 = L*L;
   double A = (-L2 + L*sqrt(16 + L2))/8;
   mAlpha = A;

   // Initialize filter variables.
   mY   = 0.0;
   mXX  = 0.0;
   mFirstFlag = true;
   printf("AlphaOne::initializeFromSigmaRatio %8.8f $ %8.8f  %8.8f $  %8.8f\n",
       mAlpha, aSigmaRatio, aDT, L);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize from step response time and threshold.

void AlphaOne::initializeFromStep(double aTs, double aStepTime, double aStepThresh)
{
   if (aStepTime < aTs) aStepTime = aTs;
   if (aStepThresh > 1) aStepThresh = 1;
   if (aStepThresh < 0) aStepThresh = 0;

   double n = aStepTime / aTs;
   double c = 1 - aStepThresh;
   double b = exp(log(c) / n);
   double a = 1 - b;

   mAlpha = a;
   mY = 0.0;
   mXX = 0.0;
   mFirstFlag = true;
   printf("AlphaOne::initializeFromStep %8.8f  $ %8.8f  %8.8f %8.8f\n", 
      mAlpha, aTs, aStepTime, aStepThresh);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set the first flag true.

void AlphaOne::setFirst()
{
   mY   = 0.0;
   mXX  = 0.0;
   mFirstFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put input value, return filtered output.

double AlphaOne::put22(double aY)
{
   if (mFirstFlag)
   {
      mFirstFlag = false;
      mXX = aY;
   }

   mY  = aY;

   double a = mAlpha;
 
   mXX = (1-a)*mXX + a*mY;

   return mXX;
}

double AlphaOne::put(bool aCondition)
{
   if (aCondition) return put(1.0);
   else            return put(0.0);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put input value, return filtered output.

double AlphaOne::put(double aY)
{
   if (mFirstFlag)
   {
      mFirstFlag = false;
      mXX = aY;
   }

   mY  = aY;

   double a = mAlpha;
   double r = mY - mXX;
   mXX = mXX + a*r;

   return mXX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize from sigma ratio, process sigma over noise sigma.

void AlphaTwo::initializeFromSigmaRatio(double aSigmaRatio,double aDT)
{
   // Calculate filter parameters.
   double L  = aSigmaRatio*aDT*aDT;
   double L2 = L*L;

   double r  = (4 + L-sqrt(8*L + L2))/4;
   double r2 = r*r;

   double A  = 1-r2;
   double B  = 2*(2-A) - 4*sqrt(1-A);

   // Store parameter variables.
   mAlpha = A;
   mBeta  = B;
   mDT    = aDT;
   if(mDT != 0) mBetaDivDT = mBeta/mDT;

   // Initialize output variables.
   mY=0.0;
   mXX=0.0;
   mXV=0.0;
   mFirstFlag = true;
   printf("AlphaTwo::initializeFromSigmaRatio %8.8f %8.8f $ %8.8f  %8.8f $  %8.8f\n",
      mAlpha, mBeta, aSigmaRatio, aDT, L);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put input value, return filtered output.

double AlphaTwo::put22(double aY)
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

   // Implement the filter.
   double a   = mAlpha;
   double b   = mBeta;
   double dt  = mDT;

   double xm = aY;
   double xk = mXX;
   double vk = mXV;
   // 6 mul, 4 add
   mXX = xk*(1-a)    + vk*(1-a)*dt + xm*a;
   mXV = xk*(-b/dt)  + vk*(1-b)    + xm*b/dt;

   // Return output.
   return mXX;
}

double AlphaTwo::put(double aY)
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

   // Implement the filter.
   double xm = aY;
   double xs = mXX;
   double vs = mXV;
   // 3 mul, 4 add
   double xp = xs + mDT*vs;
   double vp = vs;
   double rk = xm - xp;

   mXX = xp + mAlpha*rk;
   mXV = vp + mBetaDivDT*rk;

   // Return output.
   return mXX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize from sigma ratio, process sigma over noise sigma.

void AlphaThree::initializeFromSigmaRatio(double aSigmaRatio,double aDT)
{
   // Calculate filter parameters.
   double L  = aSigmaRatio*aDT*aDT;
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
   mFirstFlag = true;

   printf("AlphaThree::initializeFromSigmaRatio %8.8f %8.8f  %8.8f $ %8.8f  %8.8f $  %8.8f\n",
      mAlpha, mBeta, mGamma, aSigmaRatio, aDT, L);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put input value, return filtered output.

double AlphaThree::put22(double aY)
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

   // 9 mul, 9 add
   mXX = xk*(1-a)    + vk*(1-a)*dt + ak*(1-a)*dt2/2  + xm*a;
   mXV = xk*(-b/dt)  + vk*(1-b)    + ak*(1-b/2)*dt   + xm*b/dt;
   mXA = xk*(-g/dt2) + vk*(-g/dt)  + ak*(1-g/2)      + xm*g/dt2;

   // Return output.
   return mXX;
}

double AlphaThree::put(double aY)
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

   // 9 mul, 9 add
// mXX = xk*(1-a)    + vk*(1-a)*dt + ak*(1-a)*dt2/2  + xm*a;
// mXV = xk*(-b/dt)  + vk*(1-b)    + ak*(1-b/2)*dt   + xm*b/dt;
// mXA = xk*(-g/dt2) + vk*(-g/dt)  + ak*(1-g/2)      + xm*g/dt2;

   double mK11,mK12,mK13,mK14;
   double mK21,mK22,mK23,mK24;
   double mK31,mK32,mK33,mK34;

   mK11 = (1-a);     mK12 = (1-a)*dt;  mK13 = (1-a)*dt2/2;  mK14 = a;
   mK21 = (-b/dt);   mK22 = (1-b);     mK23 = (1-b/2)*dt;   mK24 = b/dt;
   mK31 = (-g/dt2);  mK32 = (-g/dt);   mK33 = (1-g/2);      mK34 = g/dt2;
   
   mXX = mK11*xk + mK12*vk + mK13*ak + mK14*xm;
   mXV = mK21*xk + mK22*vk + mK23*ak + mK24*xm;
   mXA = mK31*xk + mK32*vk + mK33*ak + mK34*xm;

   // Return output.
   return mXX;
}

double AlphaThree::put23(double aY)
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

   // Implement the filter.
   double a   = mAlpha;
   double b   = mBeta;
   double g   = mGamma;
   double dt  = mDT;
   double dt2 = dt*dt;

   double xm = aY;
   double xs = mXX;
   double vs = mXV;
   double as = mXA;
   double rk;
   double xp;
   double vp;

   // 6 mul, 7 add
   xp = xs + dt*vs + (dt2/2)*as;
   vp = vs + dt*as;
   rk = xm - xp;

   mXX = xp + a*rk;
   mXV = vp + (b/dt)*rk;
   mXA = as + (g/(2*dt2))*rk;
// mXA = as + (g/(dt2))*rk;
// mXA = as + (2*g/dt2)*rk;

   // Return output.
   return mXX;
}

}//namespace
}//namespace

//******************************************************************************
//******************************************************************************
//******************************************************************************
