#pragma once

/*==============================================================================

Sliding window memory min max structure class template. 

It is not thread safe.
It is not shared memory safe.

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
// This template implements an WinSize element memory structure of type T
// that provides a sliding window that maintains minimums and maximumss.

template <class T,int WinSize>
class SlidingMinMaxMean : public SlidingWindow<T, WinSize>
{
public:
   typedef SlidingWindow<T, WinSize> BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Minimum and maximum of the current occupied element values.
   T mMin;
   T mMax;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SlidingMinMaxMean()
   {
      reset();
   }

   void reset()
   {
      BaseClass::reset();
      mMin = 0;
      mMax = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.
   
   // Write an element to the array at the put index and advance
   // the put index. Calculate the minimum and maximum for all of
   // the occupied elements. Return true if full.
   bool doPut (T& aValue)
   {
      // Copy the value into the element at the put index.
      BaseClass::doPut(aValue);

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

      // Done.
      return BaseClass::mFullFlag;
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

