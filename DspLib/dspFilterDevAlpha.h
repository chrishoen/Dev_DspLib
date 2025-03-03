#pragma once

/*==============================================================================

filters
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspFilterAlpha.h"
#include "dspFilterFilters.h"

namespace Dsp
{
namespace Filter
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This filter characterizes an input signal by calculating expectations and
// uncertainties of the signal. It does this with a set of alpha filters.
// The expectation and uncertainty calculated are mean and standard deviation.

class StdDevAlpha
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Output values.
   double mX;          // Input value
   double mEX;         // Expectation (mean)
   double mUX;         // Uncertainty (standard deviation)
   double mVariance;   // Variance
   double mMean;       // Expectation (mean)
   double mStdDev;     // Uncertainty (standard deviation)

   // Alpha filters for expectation and uncertainty.
   AlphaOne mXAlpha;        // Alpha filter for input X
   AlphaOne mXSquareAlpha;  // Alpha filter for input X squared

   // Counter.
   int  mK;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   StdDevAlpha();
   void resetVars();

   // Initialize with lambda (tracking index).
   void initialize (double aLambda); 
   // Initialize with alpha.
   void initializeFromAlpha (double aP1); 
   // Initialize with lambda (tracking index).
   void initializeFromLambda (double aLambda); 
   // Initialize from step response time and threshold.
   void initializeFromStep(double aTs, double aStepTime, double aStepThresh);
   // Set the first flag true.
   void setFirst(); 

   // Put input value to calculate output variable results.
   void put(double aX);

   // Helpers.
   void show();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace
