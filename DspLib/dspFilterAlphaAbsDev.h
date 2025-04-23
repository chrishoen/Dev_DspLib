#pragma once

/*==============================================================================
filters
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include "dspFilterAlphaOne.h"

namespace Dsp
{
namespace Filter
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This nonlinear filter characterizes an input signal by calculating
// short term local expectations and uncertainties of the signal. Short
// term local expectations are calculated by alpha filters. This is
// similar to using sliding window moving averages to calculate short
// term averages.
//
// The expectation and uncertainty calculated are: 
// mean and absolute deviation.
//
// Expectation (mean) of X is E[X]
// Uncertainty (absolute deviation) is E[|X - E[X]|] is E[|X - mean|]
//
// where |X| is fabs(X)
//

template <typename real_t>
class AlphaAbsDev
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Output values.
   real_t mX;          // Input value
   real_t mEX;         // Expectation (mean)
   real_t mUX;         // Uncertainty (mean absolute deviation)
   real_t mMean;       // Expectation (mean)
   real_t mAbsDev;     // Uncertainty (mean absolute deviation)

   // Alpha filters for realtime expectation and uncertainty.
   AlphaOne<real_t> mAlphaX;        // Alpha filter for input X
   AlphaOne<real_t> mAlphaAbsDev;   // Alpha filter for absolute deviation.

   // Counter.
   int  mK;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   AlphaAbsDev()
   {
      resetVars();
   }

   // Reset. 
   void resetVars()
   {
      mX = 0.0;
      mEX = 0.0;
      mUX = 0.0;
      mMean   = 0.0;
      mAbsDev = 0.0;
      mK = 0;
   }
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize from alpha.
   void initializeFromAlpha (real_t aAlpha)
   {
      mAlphaX.initializeFromAlpha(aAlpha);
      mAlphaAbsDev.initializeFromAlpha(aAlpha);
      resetVars();
   }
   
   // Initialize from sigma ratio, process sigma over noise sigma.
   void initializeFromNoiseRatio (real_t aNoiseRatio, real_t aDT)
   {
      mAlphaX.initializeFromNoiseRatio(aNoiseRatio, aDT);
      mAlphaAbsDev.initializeFromNoiseRatio(aNoiseRatio, aDT);
      resetVars();
   }
   
   // Initialize from step response time and threshold.
   void initializeFromStep(real_t aTs, real_t aStepTime, real_t aStepThresh)
   {
      mAlphaX.initializeFromStep(aTs, aStepTime, aStepThresh);
      mAlphaAbsDev.initializeFromStep(aTs, aStepTime, aStepThresh);
      resetVars();
   
   }
   // Set the first flag true.
   void setFirst()
   {
      mAlphaX.setFirst();
      mAlphaAbsDev.setFirst();
   }
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Put input value to calculate results in the output variables.
   void put(real_t aX)
   {
      // These give moving averages (moving expectatons) of X and X the
      // absolute deviation of X 
      // E[X] and E[|X - E[X]|].
      mAlphaX.put(aX);
      mAlphaAbsDev.put((real_t)fabs(aX - mAlphaX.mXX));
   
      // X
      mX = aX;
   
      // Expectation (mean) of X is E[X]
      mEX = mAlphaX.mXX;
   
      // Absolute deviation of X is E[|X - E[X]|]
      mUX = mAlphaAbsDev.mXX;
   
      // Nicknames
      mMean   = mEX;
      mAbsDev = mUX;
   
      // Update
      mK++;
   }
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   void show()
   {
      printf("%3d %8.3f %8.3f %8.3f\n",
         mK,
         mX,
         mEX,
         mUX);
   }
   };

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace
