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

class AlphaOneFloat
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Input variable.
   float mY;

   // Output variables.
   float mXX;

   // Filter parameters
   float mAlpha;

   // True for first sample.
   bool mFirstFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize with lambda (tracking index).
   void initialize (float aLambda); 
   // Initialize with alpha.
   void initializeFromAlpha (float aP1); 
   // Initialize with lambda (tracking index).
   void initializeFromLambda (float aLambda); 
   // Initialize from step response time and threshold.
   void initializeFromStep(float aTs, float aStepTime, float aStepThresh);
   // Set the first flag true.
   void setFirst(); 

   // Put input value, return filtered output.
   float put(float aY);

   // Put input value, return filtered output.
   float put(bool aCondition);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace

