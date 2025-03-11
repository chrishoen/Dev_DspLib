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
// mean and absolute deviation.
//
// Expectation (mean) of X is E[X]
// Uncertainty (absolute deviation) is E[|X - E[X]|] is E[|X - mean|]
//
// where |X| is fabs(X)
//

class AlphaAbsDev
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Output values.
   double mX;          // Input value
   double mEX;         // Expectation (mean)
   double mUX;         // Uncertainty (mean absolute deviation)
   double mMean;       // Expectation (mean)
   double mAbsDev;     // Uncertainty (mean absolute deviation)

   // Alpha filters for realtime expectation and uncertainty.
   AlphaOne mAlphaX;        // Alpha filter for input X
   AlphaOne mAlphaAbsDev;   // Alpha filter for absolute deviation.

   // Counter.
   int  mK;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   AlphaAbsDev();
   void resetVars();

   // Initialize with alpha.
   void initializeFromAlpha (double aP1); 
   // Initialize from sigma ratio, process sigma over noise sigma.
   void initializeFromSigmaRatio (double aSigmaRatio, double aDT); 
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
