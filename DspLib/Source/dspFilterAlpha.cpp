/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <string.h>

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

void AlphaOne::initialize(double aLambda)
{
   // Calculate filter parameters.
   double L  = aLambda;
   double L2 = L*L;
   double A = (-L2 + L*sqrt(16 + L2))/8;
   mAlpha = A;

   // Initialize filter variables.
   mY   = 0.0;
   mXX  = 0.0;
}

//******************************************************************************

void AlphaOne::initializeFromAlpha(double aAlpha)
{
   mAlpha = aAlpha;
   mY   = 0.0;
   mXX  = 0.0;
}

//******************************************************************************

double AlphaOne::put(double aY)
{
   mY  = aY;
   mXX = mAlpha*mY + (1-mAlpha)*mXX;

   return mXX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void AlphaTwo::initialize(double aLambda,double aDT)
{
   // Calculate filter parameters.
   double L  = aLambda;
   double L2 = L*L;

   double r  = (4 + L-sqrt(8*L + L2))/4;
   double r2 = r*r;

   double A  = 1-r2;
   double B  = 2*(2-A) - 4*sqrt(1-A);

   // Initialize output variables.
   mAlpha = A;
   mBeta = B;

   mY=0.0;
   mXX=0.0;
   mXV=0.0;

   // Initialize filter variables.
   dt = aDT;
   xk_1 = 0.0;
   vk_1 = 0.0;
   a = A;
   b = B;
   xk = 0.0;
   vk = 0.0;
   rk = 0.0;
   xm = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

double AlphaTwo::put(double aY)
{
   // Store input.
   mY = aY;

   // Implement the filter.
   xm = aY;

   xk = xk_1 + vk_1*dt;
   vk = vk_1;

   rk = xm - xk;

   xk += a*rk;
   vk += b*rk/dt;

   xk_1 = xk;
   vk_1 = vk;

   // Store outputs.
   mXX = xk;
   mXV = vk;

   // Return output.
   return mXX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void AlphaThree::initialize(double aLambda,double aDT)
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

//******************************************************************************
//******************************************************************************
//******************************************************************************

double AlphaThree::put(double aY)
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

}//namespace
}//namespace

//******************************************************************************
//******************************************************************************
//******************************************************************************
#if 0
double AlphaThree::put(double aY)
{
   // Store input.
   mY = aY;

   // Implement the filter.
   xm = aY;

   xk = xk_1 + vk_1*dt + ak_1*(dt2/2);
   vk = vk_1 + ak_1*dt;
   ak = ak_1;

   rk = xm - xk;

   xk += (a)*rk;
   vk += (b/dt)*rk;
   ak += (g/(2*dt2))*rk;
   xk_1 = xk;
   vk_1 = vk;
   ak_1 = ak;

   // Store outputs.
   mXX = xk;
   mXV = vk;
   mXA = ak;

   // Return output.
   return mXX;
}
#endif
