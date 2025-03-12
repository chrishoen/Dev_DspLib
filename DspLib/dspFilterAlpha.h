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
// Alpha filter, first order position filter. This is a steady state kalman
// filter that gives a smoothed estimate of a target position.
// For documentation, google
// "ADA255832" or
// "FIXED-GAIN, TWO-STAGE ESTIMATORS FOR TRACKING MANEUVERING TARGETS"
// For documentation, google wikipedia
// "Alpha beta filter"
//

class AlphaOne
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Input variable.
   double mY;

   // Output variables.
   double mXX;

   // Filter parameters
   double mAlpha;

   // True for first sample.
   bool mFirstFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize from alpha.
   void initializeFromAlpha (double aP1); 
   // Initialize from sigma ratio, process sigma over noise sigma.
   void initializeFromSigmaRatio (double aSigmaRatio, double aDT); 
   // Initialize from step response time and threshold.
   void initializeFromStep(double aTs, double aStepTime, double aStepThresh);
   // Set the first flag true.
   void setFirst(); 

   // Put input value, return filtered output.
   double put(double aY);

   // Put input value, return filtered output.
   double put(bool aCondition);
   double put22(double aY);
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
// For documentation, google wikipedia
// "Alpha beta filter"

class AlphaTwo
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

   // Filter parameters.
   double mAlpha;
   double mBeta;
   double mDT;

   // Filter parameters.
   double mBetaDivDT;

   // True for first sample.
   bool mFirstFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize from sigma ratio, process sigma over noise sigma.
   void initializeFromSigmaRatio(double aSigmaRatio,double aDT); 

   // Put input value, return filtered output.
   double put22(double aY);
   double put(double aY);
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
// For documentation, google wikipedia
// "Alpha beta filter"

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

   // Filter parameters.
   double mK11,mK12,mK13,mK14;
   double mK21,mK22,mK23,mK24;
   double mK31,mK32,mK33,mK34;

   // Filter parameters.
   double mKK1,mKK2,mKK3;

   // True for first sample.
   bool mFirstFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize from sigma ratio, process sigma over noise sigma.
   void initializeFromSigmaRatio(double aSigmaRatio,double aDT); 

   // Put input value, return filtered output.
   double put22(double aY);
   double put23(double aY);
   double put(double aY);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace

