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
// where Size = N + 1, filter order is N-1.
//
// This is a finite impulse response filter that implements the
// central difference savitzky golay algorithm to obtain a first derivative
// of an input.
//
// Because the central difference introduces a fixed delay in the output of
// the first derivative, this also provides an output which is the input
// delayed by the same number of samples as the filter.
// 

// Mode  12: savitzky golay smoother polynomial degree 1,2
// Mode  34: savitzky golay smoother polynomial degree 3,4
// Mode 112: savitzky golay first derivative polynomial degree 1,2
// Mode 134: savitzky golay first derivative polynomial degree 3,4

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
   // N = 3,5,7,9
   // M = 1,2,3,4
   static const int cN = Size;
   static const int cM = (Size - 1)/2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Output variables.
   real_t mX;     // Input.
   real_t mXX;    // Delayed input.
   real_t mXV;    // First derivative of input.

   // Coefficient arrays.
   double mCArray[cM + 1];   // Intermediate coefficients.
   double mBArray[cN];       // FIR coefficients.

   // Fir filter that implements the savgol algorithm.
   FIRFilter<real_t, Size> mFilter;
   // Sliding window that implements the delay.
   SlidingWindow<real_t, cM + 1> mDelay;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
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

   // Initialize with time increment.
   void initialize(double aH)
   {
      resetVars();
      mFilter.reset();
      mDelay.reset();

      // Calculate the filter coefficients according to the mode.
      switch(Mode)
      {
         case 12:
            doCalcCoeff_Smoother_SavGol12(cN, mCArray, mBArray);
            break;
         case 34:
            doCalcCoeff_Smoother_SavGol34(cN, mCArray, mBArray);
            break;
         case 112:
            doCalcCoeff_FirstDerivative_SavGol12(cN, aH, mCArray, mBArray);
            break;
         case 134:
            doCalcCoeff_FirstDerivative_SavGol34(cN, aH, mCArray, mBArray);
            break;
         default:
            for (int i = 0; i < cN; i++) mBArray[i] = 0;
            break;
      }

      // Set the filter coefficients..
      for (int i = 0; i < cN; i++) mFilter.mB[i] = (real_t)mBArray[i];
   }
  
   // Put an input to the filter and to the sliding window.
   // Return results in the output variables.
   void doPut(real_t aInput)
   {
      // Store the input.
      mX = aInput;
      // Filter the input to obtain the first derivative.
      mXV = mFilter.put(aInput);
      // Delay the input for the same number of samples as the filter.
      if (mDelay.doPut(aInput))
      {
         // Sliding window oldest element.
         mXX = mDelay.elementAtHead();
      }
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

