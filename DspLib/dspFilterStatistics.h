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

class AlphaStatistics
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
   AlphaOne    mXAlpha;        // Alpha filter for input X
   AlphaOne    mXSquareAlpha;  // Alpha filter for input X squared

   // Counter.
   int  mK;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   AlphaStatistics();

   // Initialize.
   void initialize(double aAlpha);

   // Put input value
   void put(double aX);

   // Helpers.
   void show();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace
