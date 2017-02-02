#pragma once

/*==============================================================================
Signal history linear operator: Filter - Pavel Holoborodko central difference
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
// It implements the central difference algorithms of Pavel Holobordko to 
// calculate smoothing, first and second derivatives. The central differece
// calculations for smoothing, first and second derivatives are the same but
// with different coefficients.
 
class HistoryOperFilterHolob : public HistoryOperBase
{
public:
   typedef HistoryOperBase BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryOperFilterHolob(HistoryOperParms& aParms);
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
   // This coefficients are used to calculate the first derivative.
   void calculateCoefficientsFirstDerivative();
};

//******************************************************************************
}//namespace


