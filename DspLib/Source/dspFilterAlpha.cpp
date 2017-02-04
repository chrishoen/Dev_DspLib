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
   double L  = aLambda;
   double L2 = L*L;
   double A = (-L2 + L*sqrt(16 + L2))/8;

   mAlpha = A;
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

void AlphaTwo::initialize(double aP1, double aP2, double aDT)
{
   // X
   mX.initialize(2);
   mTempX1.initialize(2);
   mTempX2.initialize(2);

   // F
   double tFValues[2][2] = {{ (1.0 - aP1), (1.0 - aP1)*aDT },
                            { (-aP2/aDT),  (1.0 - aP2)     }};

   mF.initialize(2,2,&tFValues[0][0]);

   // G
   double tGValues[2] = { aP1, aP2/aDT };

   mG.initialize(2,&tGValues[0]);

   // Reset
   mY=0.0;
   mXX=0.0;
   mXV=0.0;
   mX.reset();
}

//******************************************************************************

void AlphaTwo::initializeFromLambda(double aL,double aDT)
{
   double L  = aL;
   double L2 = L*L;

   double r  = (4 + L-sqrt(8*L + L2))/4;
   double r2 = r*r;

   double A  = 1-r2;
   double B  = 2*(2-A) - 4*sqrt(1-A);

   initialize(A,B,aDT);
}

//******************************************************************************

double AlphaTwo::put(double aY)
{
   // Store input
   mY = aY;

   // State space calculation
   multiply (mTempX1,mF,mX);

   multiply (mTempX2,mG,aY);

   add (mX,mTempX1,mTempX2);

   // Store outputs
   mXX = mX.e(1);
   mXV = mX.e(2);

   return mXX;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void AlphaThree::initialize(double aP1,double aP2,double aP3,double aDT)
{
   // X
   mX.initialize(3);
   mTempX1.initialize(3);
   mTempX2.initialize(3);

   // Temps
   double tDT  = aDT;
   double tDT2 = aDT*aDT;
   // F
   double tFValues[3][3] = 
      {{ (1.0 - aP1),       (1.0 - aP1)*tDT, (1.0 - aP1)*tDT2/2.0 },
       { (-aP2/tDT),        (1.0 - aP2),     (1.0 - aP2/2.0)*tDT     },
       { (-aP3/tDT2),       (- aP3/tDT),     (1.0 - aP3/2.0)         }};

   mF.initialize(3,3,&tFValues[0][0]);

   // G
   double tGValues[3] = { aP1, aP2/tDT, aP3/tDT2 };

   mG.initialize(3,&tGValues[0]);

   // Reset
   mY=0.0;
   mXX=0.0;
   mXV=0.0;
   mXA=0.0;
   mX.reset();
}

//******************************************************************************

void AlphaThree::initializeFromLambda(double aL,double aDT)
{
   double L  = aL;
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

   initialize(A,B,G,aDT);
}

//******************************************************************************

double AlphaThree::put(double aY)
{
   // Store input
   mY = aY;

   // State space calculation
   multiply (mTempX1,mF,mX);

   multiply (mTempX2,mG,aY);

   add (mX,mTempX1,mTempX2);

   // Store outputs
   mXX = mX.e(1);
   mXV = mX.e(2);
   mXA = mX.e(3);

   // Done
   return mXX;
}

}//namespace
}//namespace

