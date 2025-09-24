#pragma once
/*==============================================================================
Finite impulse response filters.
==============================================================================*/

#include "dspSlidingWindow.h"
#include "dspFIRCDiffCoeff.h"
#include "dspFIRFilter.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// FIRFilter, central difference savitzky-golay for first derivative. 
// H(z)=B(z)
//
// Y[n] = B[0]*X[n] + B[1]*X[n-1] + B[2]*X[n-2] + ... + B[N]*X[n-N] 
// where Size = N + 1

template <class real_t,int Size, int Mode>
class FIRSavGol
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.
   
   // Y[n] =  B[0]*X[n] + B[1]*X[n-1] + B[2]*X[n-2] + ... + B[N-1]*X[n-N-1] 
   // Y[n] = -C[2]*X[n-2] - C[1]*X[n-1] + C[1]*X[n+1] + C[2]*X[n+2]
   static const int cN = Size;
   static const int cM = (Size - 1)/2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   real_t mX;     // Input.
   real_t mXX;    // Delayed input.
   real_t mXV;    // First derivative of input.

   double mCArray[cM + 1];
   double mBArray[cN];

   FIRFilter<real_t, Size> mFilter;
   SlidingWindow<real_t, cM + 1> mDelay;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   FIRSavGol()
   {
      resetVars();
   }

   void resetVars()
   {
      mX = 0;
      mXX = 0;
      mXV = 0;
   }

   // Initialize. 
   void initialize(double aH)
   {
      resetVars();
      mFilter.reset();
      mDelay.reset();
      
      if (Mode == 12)
      {
         doCalcCoeffFirstDerivative_SavGol12(cN, aH, mCArray, mBArray);
      }
      else if (Mode == 34)
      {
         doCalcCoeffFirstDerivative_SavGol34(cN, aH, mCArray, mBArray);
      }

      for (int i = 0; i < cN; i++) mFilter.mB[i] = (real_t)mBArray[i];
   }

   real_t doPut(real_t aInput)
   {
      mX = aInput;
      mXV = mFilter.put(aInput);
      if (mDelay.doPut(aInput))
      {
         mXX = mDelay.elementAtHead();
      }

      return mXV;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

