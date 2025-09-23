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

template <class real_t,int Size>
class FIRFilter : public SlidingWindow<real_t, Size>
{
public:
   typedef SlidingWindow<real_t, Size> BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   real_t mX;                             // Input value
   real_t mY;                             // Output value
   real_t mBArray[Size];                  // B coefficient array

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Constructors and initialization.
   FIRFilter()
   {
      reset();
   }

   void reset()
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

      // Calculate sum.
      real_t tXSum = 0;
      for (int i = 0; i < Size; i++)
      {
         tXSum += BaseClass::elementAt(i) * mBArray[i];
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

