#pragma once

/*==============================================================================
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
// This template implements a sliding window that maintains a history
// of input values and calculates minimum, maximum, and mean on it.

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
   static constexpr T cSumMultiplier =  1.0/WinSize;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Output variables. Minimum, maximum, mean of the current occupied
   // element values.
   T mMin;          // Minimum of window values.
   T mMax;          // Maximum of window values.
   T mMean;         // Mean    of window values.
   T mDelta;        // Difference between mean and previous mean.
   T mDev;          // Deviation  of input from mean.

   // Calculation variables.
   T mMeanSum;      // Sum     of window values.  
   T mPrevMean;     // Mean    of window values, previous. 

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
      mMin = 0;
      mMax = 0;
      mMean = 0;
      mMeanSum = 0;
      mDelta = 0;
      mDev = 0;
      mMeanSum = 0;
      mPrevMean = 0;
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
         mPrevMean = mInput;
         mMean = mInput;
         mDelta = 0;
         mDev = 0;
      }
      // If full.
      else
      {
         // Store previous mean.
         mPrevMean = mMean;
         // Calculate the mean as sum divided by the window size.
         mMean = mMeanSum * cSumMultiplier;
         // Calculate the delta.
         mDelta = mMean - mPrevMean;
         // Calculate the instantaneous deviation.
         mDev = mInput - mMean;
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

#if 0

SlidingWindow<int, 4>

PutIndex
0  0  put 101        min = 101 max = 101
1  1  put 102        min = 101 max = 102 
2  2  put 103        min = 101 max = 103
3  3  put 104        min = 101 max = 104
4  0  put 105        min = 102 max = 105 
6  2  put 106        min = 103 max = 106
7  3  put 107        min = 104 max = 107           
8  0  put 108        min = 105 max = 108           
9  1             
7  2
8  3



#endif

