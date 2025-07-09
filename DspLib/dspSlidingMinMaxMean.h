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
// input values and calculates the minimum, maximum, and mean on it.

template <typename T,int WinSize>
class SlidingMinMaxMean : public SlidingWindow<T, WinSize>
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
   T mMin;          // Minimum of window values.
   T mMax;          // Maximum of window values.
   T mMean;         // Mean of window values.

   // Calculation variables.
   T mMeanSum;      // Sum of window values.  

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SlidingMinMaxMean()
   {
      reset();
   }

   void reset() override
   {
      BaseClass::reset();
      mMin = 0;
      mMax = 0;
      mMean = 0;
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
      }
      // If full.
      else
      {
         // Calculate the mean as sum divided by the window size.
         mMean = mMeanSum * cSumMultiplier;
      }

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Calculate the min and max.

      // Loop through all of the occupied elements to obtain
      // the minimums and maximums.
      for (int i = 0; i < mSize; i++)
      {
         T tValue = BaseClass::elementAt(i);
         if (i==0)
         {
            mMin = tValue;
            mMax = tValue;
         }
         else
         {
            if (tValue < mMin) mMin = tValue;
            if (tValue > mMax) mMax = tValue;
         }
      }
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

