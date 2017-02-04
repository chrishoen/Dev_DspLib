#ifndef _DSPFILTERALPHA_H_
#define _DSPFILTERALPHA_H_
/*==============================================================================

filters
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "dspRVector.h"

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

class AlphaOne
{
public:
   // Initialize with lambda.
   void initialize (double aLambda); 
   // Initialize with alpha.
   void initializeFromAlpha (double aP1); 

   // Put input value, return filtered output.
   double put(double aY);

   // Input variable.
   double mY;

   // Output variables.
   double mXX;

   // Filter parameters
   double mAlpha;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Alpha Beta filter, second order iir position/velocity filter. This is a 
// steady state kalman filter that gives a smoothed estimate of a target
// position and velocity.
// For documentation, google
// "ADA255832" or
// "FIXED-GAIN, TWO-STAGE ESTIMATORS FOR TRACKING MANEUVERING TARGETS"

class AlphaTwo
{
public:
   // Initialize with lambda,DT.
   void initialize(double aLambda,double aDT); 

   // Put input value, return filtered output.
   double put(double aY);

   // Input variable.
   double mY;

   // Output variables.
   double mXX;
   double mXV;

   // Filter parameters.
   double mAlpha;
   double mBeta;

   // Filter variables.
   double dt;
   double xk_1,vk_1,a,b;
   double xk,vk,rk;
   double xm;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Alpha Beta Gamma filter, third order iir position/velocity/acceleration
// filter. This is a steady state kalman filter that gives a smoothed estimate
// of a target position, velocity , and acceleration.
// For documentation, google
// "ADA255832" or
// "FIXED-GAIN, TWO-STAGE ESTIMATORS FOR TRACKING MANEUVERING TARGETS"

class AlphaThree
{
public:
   // Initialize with alpha,beta,gamma,DT
   void initialize(double aP1,double aP2,double aP3,double aDT); 
   // Initialize with lambda,DT
   void initializeFromLambda(double aL,double aDT); 

   // Put input value
   double put(double aY);

   // Input value
   double mY;

   // Output value
   double mXX;
   double mXV;
   double mXA;

   // State space
   // X = F*X + G*Y
   RVector  mX;
   RMatrix  mF;
   RVector  mG;

   // State space temps
   RVector mTempX1;
   RVector mTempX2;
};

}//namespace
}//namespace
#endif

