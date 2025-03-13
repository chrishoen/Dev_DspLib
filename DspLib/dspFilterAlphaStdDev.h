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
// This nonlinear filter characterizes an input signal by calculating
// realtime expectations and uncertainties of the signal. Realtime 
// expectations are calculated with alpha filters. This is similar to
// using sliding window moving averages. The expectation and uncertainty
// calculated are: 
// mean and standard deviation.
//
// Expectation (mean) of X is E[X]
// Variance of X is E[X^2] - E[X]^2
// Uncertainty (standard deviation) is sqrt(Variance)
//

class AlphaStdDev
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

   // Alpha filters for realtime expectation and uncertainty.
   AlphaOne mXAlpha;        // Alpha filter for input X
   AlphaOne mXSquareAlpha;  // Alpha filter for input X squared

   // Counter.
   int  mK;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   AlphaStdDev();
   void resetVars();

   // Initialize from alpha.
   void initializeFromAlpha (double aP1); 
   // Initialize from sigma ratio, process sigma over noise sigma.
   void initializeFromNoiseRatio (double aNoiseRatio, double aDT); 
   // Initialize from step response time and threshold.
   void initializeFromStep(double aTs, double aStepTime, double aStepThresh);
   // Set the first flag true.
   void setFirst(); 

   // Put input value to calculate results in the output variables.
   void put(double aX);

   // Helpers.
   void show();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace
