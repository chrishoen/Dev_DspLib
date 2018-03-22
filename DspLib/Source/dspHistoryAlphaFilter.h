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
// It applies an alpha filter noncausally, time forward and backward.
 
class HistoryAlphaFilter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Alpha filter.
   Dsp::Filter::AlphaOne mAlphaOne;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryAlphaFilter();
   HistoryAlphaFilter(double aAlpha);
   void initialize(double aAlpha);

   // Apply the linear operator from the input to the output. F:X->Y.
   // Apply an alpha filter from the input history to the output history,
   // forward in time. Then apply an alpha filter from the output history 
   // to the output history backward in time (time reversal). This results 
   // in a noncausal second order low pass filter that has zero phase
   // response.
   void operate(History& aX,History& aY);

};

//******************************************************************************
}//namespace

