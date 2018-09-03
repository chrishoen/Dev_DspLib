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
   // Initialize with lambda (tracking index).
   void initialize (double aLambda); 
   // Initialize with alpha.
   void initializeFromAlpha (double aP1); 
   // Initialize with lambda (tracking index).
   void initializeFromLambda (double aLambda); 
   // Set the first lag true.
   void setFirst(); 

   // Put input value, return filtered output.
   double put(double aY);

   // Input variable.
   double mY;

   // Output variables.
   double mXX;

   // Filter parameters
   double mAlpha;

   // True for first sample.
   bool mFirstFlag;
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
   // Initialize with lambda,DT (tracking index, time increment).
   void initialize(double aLambda,double aDT); 

   // Put input value, return filtered output.
   double put(double aY);

   // Input variable.
   double mY;

   // Filter state output variables.
   double mXX;
   double mXV;

   // Filter parameters.
   double mAlpha;
   double mBeta;
   double mDT;
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
   // Initialize with lambda,DT (tracking index, time increment).
   void initialize(double aLambda,double aDT); 

   // Put input value, return filtered output.
   double put(double aY);

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
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace

