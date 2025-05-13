#pragma once

/*==============================================================================
Sliding window.
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
// This template implements a sliding window that maintains a history of
// input values and calculates the mean on it. It also calculates a delta 
// that, in some cases, can be used to indicate if the input is increasing
// or decreasing.

template <typename T,int WinSize>
class SlidingMean : public SlidingWindow<T, WinSize>
{
public:
   typedef SlidingWindow<T, WinSize> BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // Used to divide by the window size.
   static constexpr T cSumMultiplier =  ((T)1)/((T)WinSize);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Output variables.
   T mMean;         // Mean of window values.
   T mDelta;        // Difference between head and tail window values.

   // Calculation variables.
   T mMeanSum;      // Sum of window values.  

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SlidingMean()
   {
      reset();
   }

   void reset() override
   {
      BaseClass::reset();
      mMean = 0;
      mDelta = 0;
      mMeanSum = 0;
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
         mMeanSum -= elementAtTail();
      }

      // Add the input value to the sum.
      mMeanSum += mInput;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This is called by the base class put operation after the actual put.

   void doAfterPut() override
   {
      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Calculate the mean and related variables.

      // If not full yet.
      if (!BaseClass::mFullFlag)
      {
         // Initialize.
         mMean = mInput;
         mDelta = 0;
      }
      // If full.
      else
      {
         // Calculate the mean as sum divided by the window size.
         mMean = mMeanSum * cSumMultiplier;
         // Calculate the delta.
         mDelta = elementAtHead() - elementAtTail();
      }
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

