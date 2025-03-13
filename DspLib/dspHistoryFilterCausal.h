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
#include "dspFilterAlphaStdDev.h"
#include "dspFilterAlphaAbsDev.h"

#include "dspFilterAlphaOne.h"
#include "dspFilterAlphaTwo.h"
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a linear operator on the set of signal histories:  
// It applies some recursive filters causally.
 
class HistoryFilterCausal
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
// Dsp::Filter::AlphaOne  mAlphaOne;
   Dsp::Filter::AlphaOneT<float>  mAlphaOne;
// Dsp::Filter::AlphaTwo      mAlphaTwo;
   Dsp::Filter::AlphaTwoT<float>  mAlphaTwo;
   Dsp::Filter::AlphaThree    mAlphaThree;
   Dsp::Filter::AlphaStdDev   mAlphaStdDev;
   Dsp::Filter::AlphaAbsDev   mAlphaAbsDev;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryFilterCausal(HistoryFilterParms& aParms);
   void show();

   // Apply the linear operator from the input to the output. F:X->Y
   void operate(History& aX,History& aY);

   // Apply the linear operator from the input to two outputs. F:X->Y1,Y2
   void operate(History& aX,History& aY1,History& aY2);

   // Apply the linear operator from the input to two outputs. F:X->Y1,Y2
   void operate(History& aX,History& aY1,History& aY2,History& aY3);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize the causal filter, based on the parms.
   void initializeCausalFilter();

   // Put an input to the filter, return the output.
   void putToFilter(double aInput,double* aOutput);
   void putToFilter(double aInput,double* aOutput1,double* aOutput2);
   void putToFilter(double aInput,double* aOutput1,double* aOutput2,double* aOutput3);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


