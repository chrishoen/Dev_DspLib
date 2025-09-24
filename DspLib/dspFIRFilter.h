#pragma once
/*==============================================================================
Finite impulse response filters.
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
// FIRFilter, see wikipedia or matlab for definition
// H(z)=B(z)
// 
// Y[n] = B[0]*X[n] + B[1]*X[n-1] + B[2]*X[n-2] + ... + B[N]*X[n-N] 
// where Size = N + 1, filter order is N-1.

template <class real_t,int Size>
class FIRFilter : public SlidingWindow<real_t, Size>
{
public:
   typedef SlidingWindow<real_t, Size> BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   real_t mX;             // Input value.
   real_t mY;             // Output value.
   real_t mB[Size];  // B coefficient array.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Constructor.
   FIRFilter()
   {
      resetVars();
   }

   void resetVars()
   {
      mX = 0;
      mY = 0;
   }

   // Called by base class after the input value was put to window. 
   void doAfterPut() override
   {
      // Guard
      if (!BaseClass::mFullFlag)
      {
         mX = 0;
         mY = 0;
         return;
      }

      // Store.
      mX = BaseClass::mInput;

      // Calculate sum. Loop from most recent to least recent.
      real_t tXSum = 0;
      for (int i = 0; i < Size; i++)
      {
         tXSum += BaseClass::elementAt(i) * mB[i];
      }
      mY = tXSum;
   }

   // Apply the filter.
   real_t put(real_t aInput)
   {
      // Put to the sliding window. This will call the after function,
      // which implements the filter. 
      BaseClass::doPut(aInput);
      return mY;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

