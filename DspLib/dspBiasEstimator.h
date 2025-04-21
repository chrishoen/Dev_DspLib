#pragma once

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include "dspFilterAlphaOne.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This estimates a bias in a signal that is can be characterized as a 
// superposition of a constant bias and an intermettent disturbance (for
// example, a pulse train). 
//
// It estimates the bias in the signal by taking a short term local averages
// (moving average) of signal values that are sampled when the signal is deemed
// to be not changing. It determines that the signal is not changing as when
// its instantaneous absolute deviation from a short term local average is less
// than a threshold. 
//
// Also, it only considers signal values that are within upper and lower
// limits. Short term local averages are calculated with alpha filters.

template <typename real_t>
class BiasEstimator
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Ignore inputs that are outside of these limits.
   real_t mLimitHi;
   real_t mLimitLo;

   // If the instantaneous absolute deviation from a short term average
   // is less than this threshold then add the input to the bias average.
   real_t mThreshDev;

   // Output values.
   real_t mX;          // Input value
   real_t mMean;       // Expectation of input (mean)
   real_t mAbsDev;     // Instantaneous absolute deviation.
   real_t mBias;       // Bias (mean of when in limits and not changing)

   // True if at least one input value was within the limits and was not
   // changing.
   bool mValidFlag;

   // Alpha filters for short term local averages.
   Filter::AlphaOneT<real_t> mAlphaX;        // Alpha filter for input X
   Filter::AlphaOneT<real_t> mAlphaBias;     // Alpha filter for bias.

   // Counter.
   int  mK;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   BiasEstimator()
   {
      resetVars();
   }

   // Reset. 
   void resetVars()
   {
      mLimitHi = (real_t)100000;
      mLimitLo = (real_t)0;
      mThreshDev = (real_t)10;

      mX = 0.0;
      mMean   = 0.0;
      mAbsDev = 0.0;
      mK = 0;
      mValidFlag = false;
   }
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize from alpha.
   void initializeFromAlpha (real_t aAlpha)
   {
      mAlphaX.initializeFromAlpha(aAlpha);
      mAlphaBias.initializeFromAlpha(aAlpha);
      resetVars();
   }
   
   // Initialize from sigma ratio, process sigma over noise sigma.
   void initializeFromNoiseRatio (real_t aNoiseRatio, real_t aDT)
   {
      mAlphaX.initializeFromNoiseRatio(aNoiseRatio, aDT);
      mAlphaBias.initializeFromNoiseRatio(aNoiseRatio, aDT);
      resetVars();
   }
   
   // Initialize from step response time and threshold.
   void initializeFromStep(real_t aTs, real_t aStepTime, real_t aStepThresh)
   {
      mAlphaX.initializeFromStep(aTs, aStepTime, aStepThresh);
      mAlphaBias.initializeFromStep(aTs, aStepTime, aStepThresh);
      resetVars();
   
   }
   // Set the first flag true.
   void setFirst()
   {
      mAlphaX.setFirst();
      mAlphaBias.setFirst();
   }
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Put input value to calculate results in the output variables.
   void put(real_t aX)
   {
      // Save the input.
      mX = aX;

      // Ignore inputs that are outside of the limits.
      if (aX < mLimitLo || aX > mLimitHi) return;

      // Calculate the short term local average of X (moving average).
      // E[X].
      mAlphaX.put(aX);

      // Expectation (mean) of X is E[X]
      mMean = mAlphaX.mXX;
   
      // Calculate the instantaneous absolute deviation from the short
      // term local average.
      // |X - E[X]|
      mAbsDev = (real_t)fabs(aX - mAlphaX.mXX);

      // If the absolute deviation is greater than the threshold then
      // ignore the input.
      if (mAbsDev > mThreshDev) return;

      // At this point the input is within the limits and it is
      // not changing. Add it to the short term bias average.
      mAlphaBias.put(aX);
   
      // Short term local bias average.
      mBias = mAlphaBias.mXX;

      // Update
      mValidFlag = true;
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
