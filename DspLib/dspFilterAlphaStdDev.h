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

template <typename real_t>
class AlphaStdDev
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Output values.
   real_t mX;          // Input value
   real_t mEX;         // Expectation (mean)
   real_t mUX;         // Uncertainty (standard deviation)
   real_t mVariance;   // Variance
   real_t mMean;       // Expectation (mean)
   real_t mStdDev;     // Uncertainty (standard deviation)

   // Alpha filters for realtime expectation and uncertainty.
   AlphaOne<real_t> mXAlpha;        // Alpha filter for input X
   AlphaOne<real_t> mXSquareAlpha;  // Alpha filter for input X squared

   // Counter.
   int  mK;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   AlphaStdDev()
   {
      resetVars();
   }

   // Reset varieables.
   void resetVars()
   {
      mX = 0.0;
      mEX = 0.0;
      mUX = 0.0;
      mVariance = 0.0;
      mMean   = 0.0;
      mStdDev = 0.0;
      mK = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize from alpha.
   void initializeFromAlpha (real_t aAlpha)
   {
      mXAlpha.initializeFromAlpha(aAlpha);
      mXSquareAlpha.initializeFromAlpha(aAlpha);
      resetVars();
   }

   // Initialize from noise ratio, process sigma over noise sigma.
   void initializeFromNoiseRatio (real_t aNoiseRatio, real_t aDT)
   {
      mXAlpha.initializeFromNoiseRatio(aNoiseRatio, aDT);
      mXSquareAlpha.initializeFromNoiseRatio(aNoiseRatio, aDT);
      resetVars();
   }

   // Initialize from step response time and threshold.
   void initializeFromStep(real_t aTs, real_t aStepTime, real_t aStepThresh)
   {
      mXAlpha.initializeFromStep(aTs, aStepTime, aStepThresh);
      mXSquareAlpha.initializeFromStep(aTs, aStepTime, aStepThresh);
      resetVars();

   }
   // Set the first flag true.
   void setFirst()
   {
      mXAlpha.setFirst();
      mXSquareAlpha.setFirst();
   }

   //************************************************************************
   //************************************************************************
   //************************************************************************
   // Methods.

   // Put input value to calculate results in the output variables.
   void put(real_t aX)
   {
      // These give moving averages (moving expectatons) of X and X squared.
      // E[X] and E[X^2].
      mXAlpha.put(aX);
      mXSquareAlpha.put(aX*aX);

      // X
      mX = aX;

      // Expectation (mean) of X is E[X]
      mEX = mXAlpha.mXX;

      // Variance of X is E[X^2] - E[X]^2
      mVariance = mXSquareAlpha.mXX - mEX*mEX;

      // Uncertainty (stddev) of X
      if (mVariance > 0.0)
      {
         mUX = (real_t)sqrt(mVariance);
      }
      else
      {
         mUX = 0.0f;
      }

      // Nicknames
      mMean   = mEX;
      mStdDev = mUX;

      // Update
      mK++;
   }

   //************************************************************************
   //************************************************************************
   //************************************************************************
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
