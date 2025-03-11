#pragma once

/*==============================================================================
Signal history linear operator: the identity operator.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspHistoryFilterParms.h"
#include "dspHistory.h"
#include "dspFilterButterworth.h"
#include "dspFilterAlpha.h"

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
// This class provides a linear operator on the set of signal histories:  
// It applies some recursive filters causally.
 
class HistoryFilterNoncausal
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameters. These are read from a parms file.

   HistoryFilterParms mParms;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   Dsp::Filter::ButterworthLP mButterworth;
   Dsp::Filter::AlphaOne      mAlphaOne;
   Dsp::Filter::AlphaTwo      mAlphaTwo;
   Dsp::Filter::AlphaThree    mAlphaThree;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryFilterNoncausal(HistoryFilterParms& aParms);
   void show();

   // Apply the linear operator from the input to the output. F:X->Y
   void operate(History& aX,History& aY);
   void operate(History& aX,History& aY1,History& aY2);
   void operate(History& aX,History& aY1,History& aY2,History& aY3);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize the causal filter, based on the parms.
   void initializeCausalFilter();

   // Put an input to the filter, return the output.
   void putToFilterForward (double aInput,double* aOutput);
   void putToFilterBackward(double aInput,double* aOutput);
   void putToFilterBackward(double aInput,double* aOutput1,double* aOutput2);
   void putToFilterBackward(double aInput,double* aOutput1,double* aOutput2,double* aOutput3);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


