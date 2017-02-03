#pragma once

/*==============================================================================
Signal history linear operator: Filter - Savitzky-Golay central difference
algorithms for smoothing, first and second derivates.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"

#include "dspHistoryOperParms.h"
#include "dspHistoryOperBase.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a linear operator on the set of signal histories.
// It implements the central difference algorithms of Savitzky-Golay to 
// calculate smoothing, first and second derivatives. The central differece
// calculations for smoothing, first and second derivatives are the same but
// with different coefficients.
 
class HistoryOperFilterSavGol : public HistoryOperBase
{
public:
   typedef HistoryOperBase BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // If true then add backward terms, else subtract.
   // Central difference filters are symmetric or asymetric. The coefficients
   // for forward time and backward time are the same. Forward terms are added
   // to the accumulator. Backward terms are either added or subtracted,
   // depending on the type. Smoothers add the backward terms, first
   // derivatives subtract, and second derivatives add.
   bool mBackAddFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryOperFilterSavGol(HistoryOperParms& aParms);
   void show();

   // Apply the linear operator from the input to the output. F:X->Y.
   // This applies the central difference filter using the coefficients 
   // calculated below.
   void operate(History& aX, History& aY) override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Calculate the central difference filter coefficents, based on the parms.
   // This coefficients are used to calculate a smoothed output.
   void calculateCoefficientsSmoother1();
   void calculateCoefficientsSmoother2();

   // Calculate the central difference filter coefficents, based on the parms.
   // This coefficients are used to calculate the first derivative.
   void calculateCoefficientsFirstDerivative1();
   void calculateCoefficientsFirstDerivative2();

   // Calculate the central difference filter coefficents, based on the parms.
   // This coefficients are used to calculate the first derivative.
   void calculateCoefficientsSecondDerivative1();
};

//******************************************************************************
}//namespace


