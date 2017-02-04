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

#include "dspFilterAlphaSS.h"

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

void AlphaOneSS::initialize(double aP1)
{
   mP1  = aP1;
   mAP1 = 1.0 - aP1;

   mY   = 0.0;
   mXX  = 0.0;
   mK   = 0;
}

//******************************************************************************

void AlphaOneSS::initializeFromLambda(double aL)
{
   double L  = aL;
   double L2 = L*L;
   double A = (-L2 + L*sqrt(16 + L2))/8;
   initialize(A);
}

//******************************************************************************

double AlphaOneSS::put(double aY)
{
   mY  = aY;
   mXX = mP1 * aY + mAP1 * mXX;

   mK++;
   return mXX;
}

//******************************************************************************

void AlphaOneSS::show()
{
   printf("%3d $$ %8.3f %8.3f\n",
      mK,
      mY,
      mXX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void AlphaTwoSS::initialize(double aP1, double aP2, double aDT)
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
   mK  = 0;
}

//******************************************************************************

void AlphaTwoSS::initializeFromLambda(double aL,double aDT)
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

double AlphaTwoSS::put(double aY)
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

   // Done
   mK++;
   return mXX;
}

//******************************************************************************

void AlphaTwoSS::show()
{
   printf("%3d $$ %8.3f %8.3f %8.3f\n",
      mK,
      mY,
      mXX,
      mXV);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void AlphaThreeSS::initialize(double aP1,double aP2,double aP3,double aDT)
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
   mK  = 0;
}

//******************************************************************************

void AlphaThreeSS::initializeFromLambda(double aL,double aDT)
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

double AlphaThreeSS::put(double aY)
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
   mK++;
   return mXX;
}

//******************************************************************************

void AlphaThreeSS::show()
{
   printf("%3d $$ %8.3f %8.3f %8.3f %8.3f\n",
      mK,
      mY,
      mXX,
      mXV,
      mXA);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void PropagatorSS::initialize(double aX0,double aXV,double aDT)
{
   mXX = aX0;
   mDX = aXV*aDT;
}

//******************************************************************************

double PropagatorSS::update()
{
   // Integrate
   mXX += mDX;

   // Done
   mK++;
   return mXX;
}
}//namespace
}//namespace

