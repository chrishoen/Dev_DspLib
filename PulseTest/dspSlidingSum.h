#pragma once

/*==============================================================================
Sliding window sum.
==============================================================================*/

#include "dspSlidingWindow.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This template implements a sliding window that maintains a sum of
// input values.

template <typename SumT, typename ElementT, int WinSize>
class SlidingSum : public SlidingWindow<ElementT, WinSize>
{
public:
   typedef SlidingWindow<ElementT, WinSize> BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Control variables.
   SumT mSumHigh;
   SumT mSumLow;

   // Output variables.
   SumT mSum;         // Sum of window values.
   bool mHighFlag;    // True if sum is high.
   bool mLowFlag;     // True if sum is low.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SlidingSum()
   {
      reset();
   }

   void reset() override
   {
      BaseClass::reset();
      mSum = 0;
      mSumHigh = 0;
      mSumLow = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This is called by the base class put operation before the actual put.

   void doBeforePut() override
   {
      // If full.
      if (BaseClass::mFullFlag)
      {
         // Subtract the tail value from the sum.
         mSum -= (SumT)elementAtTail();
      }

      // Add the input value to the sum.
      mSum += (SumT)mInput;

      // Compare the sum.
      mHighFlag = mSum >= mSumHigh;
      mLowFlag = mSum <= mSumLow;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

